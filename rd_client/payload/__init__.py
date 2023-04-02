import enum

class OperationCodes(enum.Enum):
    """Enum of operation codes."""
    SET_EDITABLE            = 1
    GET_EDITABLE            = 2
    CLEAR_DATA              = 3
    PUSH_DATA               = 4
    POP_DATA                = 5
    GET_DEBUG_LINE          = 6
    INC_DEBUG_LINE          = 7
    RESET_DEBUG_LINE_INDEX  = 8
    RESPONSE_OK             = 9
    RESPONSE_ERR            = 10


class PayloadFormatError(Exception):
    """Triggered when payload the conditions required by the operation are not met."""
    pass


def create_payload(op_code: OperationCodes, data: bytes|None=None) -> bytearray:
    """Create a payload ready to be send to the device.

    Params:
        op_code (OperationCodes): Type of operation.
        data (bytes|None): List of bytes to send to the device.
                              Defaults to None.

    Raises:
        PayloadFormatError: Missing or wrong data required by the payload's
                            operation.

    Returns:
        (bytearray): Created payload.
    """
    _ba = bytearray()
    # first byte is operation code
    # second byte is size of the payload
    # third byte onwards contains the data itself
    _ba.append(op_code.value)
    _ba.append(0)   # reserved
    if (op_code == OperationCodes.SET_EDITABLE):
        # check the format
        if (not data or
            len(data) > 1 or
            (data[0] != 0 and data[0] != 1)
        ):
            raise PayloadFormatError()
        # append payload_len and payload itself
        _ba.extend((1).to_bytes(2, 'little'))
        _ba.extend(data)

    elif op_code == OperationCodes.PUSH_DATA:
        if not data:
            raise PayloadFormatError()
        # append payload_len and payload itself
        _ba.extend(len(data).to_bytes(2, 'little'))
        _ba.extend(data)

    elif (
        op_code == OperationCodes.GET_EDITABLE or
        op_code == OperationCodes.CLEAR_DATA or
        op_code == OperationCodes.POP_DATA or
        op_code == OperationCodes.GET_DEBUG_LINE or
        op_code == OperationCodes.INC_DEBUG_LINE or
        op_code == OperationCodes.RESET_DEBUG_LINE_INDEX
    ):
        # append payload_len and payload itself
        _ba.extend((0).to_bytes(2, 'little'))
    return _ba
