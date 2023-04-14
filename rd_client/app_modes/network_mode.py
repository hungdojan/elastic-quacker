import logging
import socket
import sys

from rd_client.parser import KeySeqvParser
from rd_client.parser.error import ParserError
from rd_client.payload import create_payload, OperationCodes

from .base import BaseMode

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


    def __format_recv_msg(self, prefix: str, buffer: bytes) -> str:
        """Format the received packet."""

        prefix_str = f'{prefix} - {OperationCodes(int(buffer[0])).name}: '
        data_str = ''
        if int(buffer[0]) == OperationCodes.RESPONSE_OK.value:
            # display hex format
            data_str += ' '.join([f'{val:02x}{" " if (i+1) % 8 == 0 else ""}'
                                  for i, val in enumerate(buffer)])
        elif len(buffer) > 4:
            # expected error message
            data_str += buffer[4:-1].decode()
        return f'{prefix_str:<23}[{data_str}]'


    def __format_sent_msg(self, prefix: str, buffer: bytes) -> str:
        """Format the sent packet."""

        prefix_str = f'{prefix} - {OperationCodes(int(buffer[0])).name}: '
        data_str = ''
        # format_str = f'{prefix} - {OperationCodes(int(buffer[0])).name}: '
        if len(buffer) > 4:
            # display hex format
            data_str += ' '.join([f'{val:02x}{" " if (i+1) % 8 == 0 else ""}'
                                  for i, val in enumerate(buffer[4:])])
        return f'{prefix_str:<23}[{data_str}]'


    def run(self) -> int:

        def _enable_read_write_mode(socket: socket.socket, enable_read_write: int) -> bool:
            val = bytearray()
            val.append(1 if enable_read_write else 0)
            msg = create_payload(OperationCodes.SET_EDITABLE, bytes(val))
            socket.send(msg)
            self._log_msg(logging.INFO, self.__format_sent_msg('Sent', msg))

            recv_msg = socket.recv(self.__SOCKET_BUFFER_SIZE)
            self._log_msg(logging.INFO, self.__format_recv_msg('Recv', recv_msg))

            if int(recv_msg[0]) == OperationCodes.RESPONSE_ERR.value:
                return False

            # clear the list when enabling read write mode
            if enable_read_write:
                msg = create_payload(OperationCodes.CLEAR_DATA)
                socket.send(msg)
                self._log_msg(logging.INFO, self.__format_sent_msg('Sent', msg))

                recv_msg = socket.recv(self.__SOCKET_BUFFER_SIZE)
                self._log_msg(logging.INFO, self.__format_recv_msg('Recv', recv_msg))
            return True

        def _send_run_command(socket: socket.socket):
            msg = create_payload(OperationCodes.RUN_SEQUENCES)
            socket.send(msg)
            self._log_msg(logging.INFO, self.__format_sent_msg('Sent', msg))
            recv_msg = socket.recv(self.__SOCKET_BUFFER_SIZE)
            self._log_msg(logging.INFO, self.__format_recv_msg('Recv', recv_msg))

        ksp = KeySeqvParser(self._verbose)

        self._log_msg(logging.INFO, '------ Start parsing script ------')
        try:
            # reading file
            with self._in_f as f:
                for i, line in enumerate(f):
                    ksp.parse_line(line, i)
            ksp.set_last()
        except ParserError:
            self._log_msg(logging.ERROR, 'Terminating application')
            self._display_nonverbose_error_msg()
            return 1

        self._log_msg(logging.INFO, '------ Connecting to host... ------')
        # opening socket
        client_socket = socket.socket()
        client_socket.connect((self._host, self._port))

        self._log_msg(logging.INFO, '--------- Sending to host ---------')
        # enable writing mode
        _enable_read_write_mode(client_socket, True)

        # sending data to RubberDucky
        for i, ks in enumerate(ksp.lof_keyseqvs):
            # creating payload
            msg = create_payload(OperationCodes.PUSH_DATA, bytes(ks.to_bytes()))

            client_socket.send(msg)
            self._log_msg(logging.INFO, self.__format_sent_msg('Sent', msg))
            recv_msg = client_socket.recv(self.__SOCKET_BUFFER_SIZE)

            # format the string
            # display hex value of the byte
            # add bigger delimiter after 8th byte
            self._log_msg(logging.INFO, self.__format_recv_msg('Recv', recv_msg))

        # disable writing mode and run the sequences
        _enable_read_write_mode(client_socket, False)
        _send_run_command(client_socket)

        client_socket.close()
        self._log_msg(logging.INFO, '----- Paylod successfully sent -----')
        return 0
