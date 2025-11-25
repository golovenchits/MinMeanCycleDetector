import struct

# Path to your binary file
filename = "10_40.mcm"

with open(filename, "rb") as f:
    data = f.read(4)          # a float is 4 bytes
    value = struct.unpack('f', data)[0]

print(value)