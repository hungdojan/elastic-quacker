import logging
import socket
import sys

from .base import BaseMode
from rd_client.parser import KeySeqvParser
from rd_client.payload import create_payload, OperationCodes

class NetworkMode(BaseMode):
    """Cli mode for sending RubberDucky script to RubberDucky device using
        network's server-client method."""

    START_BYTE = (0xd0).to_bytes(1, 'little')
    END_BYTE = (0xd0).to_bytes(1, 'little')

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
        ksp = KeySeqvParser(self._verbose)

        # opening socket
        client_socket = socket.socket()
        client_socket.connect((self._host, self._port))
        self._log_msg(logging.INFO, '------ Start parsing script ------')

        # reading file
        with self._in_f as f:
            for i, line in enumerate(f):
                ksp.parse_line(line, i)
        ksp.set_last()

        self._log_msg(logging.INFO, '--------- Sending to host ---------')
        # sending data to RubberDucky
        for i, ks in enumerate(ksp.lof_keyseqvs):
            # creating payload
            # TODO: new payload format
            # | op | len | data |
            # msg = self.START_BYTE
            # msg += bytes(ks.to_bytes())
            # msg += self.END_BYTE
            msg = create_payload(OperationCodes.PUSH_DATA, bytes(ks.to_bytes()))

            client_socket.send(msg)
            self._log_msg(logging.INFO, f'Sent: {i+1}. sequence')
            recv_msg = client_socket.recv(200)

            # format the string
            # display hex value of the byte
            # add bigger delimiter after 8th byte
            format_str = ' '.join([f'{val:02x}{" " if (i+1) % 8 == 0 else ""}'
                                   for i, val in enumerate(recv_msg)])
            self._log_msg(logging.INFO, f'Recv: {format_str}')

        client_socket.close()
        self._log_msg(logging.INFO, '----- Paylod successfully sent -----')
