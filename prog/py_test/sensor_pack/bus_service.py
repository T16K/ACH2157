from machine import I2C


class BusAdapter:
    def __init__(self, bus):
        self.bus = bus

    def read_register(self, device_addr: int, reg_addr: int, bytes_count: int) -> bytes:
        raise NotImplementedError

    def write_register(self, device_addr: int, reg_addr: int, value: int,
                       bytes_count: int, byte_order: str):
        raise NotImplementedError

    def read(self, device_addr, n_bytes: int) -> bytes:
        raise NotImplementedError

    def write(self, device_addr, buf: bytes):
        raise NotImplementedError


class I2cAdapter(BusAdapter):
    def __init__(self, bus: I2C):
        super().__init__(bus)

    def write_register(self, device_addr: int, reg_addr: int, value: int,
                       bytes_count: int, byte_order: str):
        buf = value.to_bytes(bytes_count, byte_order)
        return self.bus.writeto_mem(device_addr, reg_addr, buf)

    def read_register(self, device_addr: int, reg_addr: int, bytes_count: int) -> bytes:
        return self.bus.readfrom_mem(device_addr, reg_addr, bytes_count)

    def read(self, device_addr, n_bytes: int) -> bytes:
        return self.bus.readfrom(device_addr, n_bytes)

    def write(self, device_addr, buf: bytes):
        return self.bus.writeto(device_addr, buf)
