import micropython
import ustruct
from sensor_pack import bus_service


class BaseSensor:

    def __init__(self, adapter: bus_service.BusAdapter, address: int, big_byte_order: bool):
        self.adapter = adapter
        self.address = address
        self.big_byte_order = big_byte_order

    def _get_byteorder_as_str(self) -> tuple:
        if self.is_big_byteorder():
            return 'big', '>'
        else:
            return 'little', '<'

    def unpack(self, fmt_char: str, source: bytes) -> tuple:
        fmt_char: c, b, B, h, H, i, I, l, L, q, Q. 
        if len(fmt_char) != 1:
            raise ValueError(f"Invalid length fmt_char parameter: {len(fmt_char)}")
        bo = self._get_byteorder_as_str()[1]
        return ustruct.unpack(bo + fmt_char, source)

    @micropython.native
    def is_big_byteorder(self) -> bool:
        return self.big_byte_order

    def get_id(self):
        raise NotImplementedError

    def soft_reset(self):
        raise NotImplementedError


class Iterator:
    def __iter__(self):
        return self

    def __next__(self):
        raise NotImplementedError
