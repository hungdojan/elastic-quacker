import logging
import socket
import sys

from .base import BaseMode
from rd_client.parser import KeySeqvParser
from rd_client.payload import create_payload, OperationCodes

class NetworkMode(BaseMode):
    """Cli mode for sending RubberDucky script to RubberDucky device using
        network's server-client method."""

    __SOCKET_BUFFER_SIZE=1024
    def __init__(self, input_file: str|None, port: int, ip_addr: str, verbose: bool):
        super().__init__(verbose)
        self._port = port
        self._host = ip_addr

        # input file
        if input_file:
            self._in_f = open(input_file, 'r')
        else:
            self._in_f = sys.stdin


    def run(self):

        def _enable_read_write_mode(socket: socket.socket, enable_read_write: int) -> bool:
            val = bytearray()
            val.append(1 if enable_read_write else 0)
            msg = create_payload(OperationCodes.SET_EDITABLE, bytes(val))
            socket.send(msg)
            self._log_msg(logging.INFO, f'Recv: {msg}')
            recv_msg = socket.recv(self.__SOCKET_BUFFER_SIZE)

            # FIXME: log messages
            if int(recv_msg[0]) == OperationCodes.RESPONSE_OK.value:
                self._log_msg(logging.INFO, f'Recv: {recv_msg}')
            else:
                self._log_msg(logging.WARN, f'Recv: {recv_msg}')

            # clear the list when enabling read write mode
            if enable_read_write:
                msg = create_payload(OperationCodes.CLEAR_DATA)
                socket.send(msg)
                recv_msg = socket.recv(self.__SOCKET_BUFFER_SIZE)
                if int(recv_msg[0]) == OperationCodes.RESPONSE_OK.value:
                    self._log_msg(logging.INFO, f'Recv: {recv_msg}')
                else:
                    self._log_msg(logging.WARN, f'Recv: {recv_msg}')
                pass
            return True

        ksp = KeySeqvParser(self._verbose)

        self._log_msg(logging.INFO, '------ Start parsing script ------')

        # reading file
        with self._in_f as f:
            for i, line in enumerate(f):
                ksp.parse_line(line, i)
        ksp.set_last()
        self._log_msg(logging.INFO, '-------- Connecting to host -------')
        # opening socket
        client_socket = socket.socket()
        client_socket.connect((self._host, self._port))

        self._log_msg(logging.INFO, '--------- Sending to host ---------')
        _enable_read_write_mode(client_socket, True)
        # sending data to RubberDucky
        for i, ks in enumerate(ksp.lof_keyseqvs):
            # creating payload
            msg = create_payload(OperationCodes.PUSH_DATA, bytes(ks.to_bytes()))

            client_socket.send(msg)
            self._log_msg(logging.INFO, f'Sent: {i+1}. sequence: {msg}')
            recv_msg = client_socket.recv(self.__SOCKET_BUFFER_SIZE)

            # format the string
            # display hex value of the byte
            # add bigger delimiter after 8th byte
            format_str = ' '.join([f'{val:02x}{" " if (i+1) % 8 == 0 else ""}'
                                    for i, val in enumerate(recv_msg)])
            self._log_msg(logging.INFO, f'Recv: {format_str}')

        _enable_read_write_mode(client_socket, False)
        client_socket.close()
        self._log_msg(logging.INFO, '----- Paylod successfully sent -----')
