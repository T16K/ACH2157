from sensor_pack.base_sensor import BaseSensor, Iterator
import ustruct


class Bh1750(BaseSensor, Iterator):

    def __del__(self):
        self.power(False)

    def _send_cmd(self, command: int):
        bo = self._get_byteorder_as_str()[0]
        self.adapter.write(self.address, command.to_bytes(1, bo))

    def get_id(self):
        return None

    def soft_reset(self):
        self._send_cmd(0b0000_0111)

    def power(self, on_off: bool = True):
        if on_off:
            self._send_cmd(0b0000_0001)
        else:
            self._send_cmd(0b0000_0000)

    def set_mode(self, continuously: bool = True, high_resolution: bool = True):
        if continuously:
            cmd = 0b0001_0000
        else:
            cmd = 0b0010_0000

        if not high_resolution:
            cmd |= 0b11

        self._send_cmd(cmd)

    def get_illumination(self) -> int:
        tmp = self.adapter.read(self.address, 2)
        return self.unpack("H", tmp)[0]

    def __next__(self) -> int:
        return self.get_illumination()
