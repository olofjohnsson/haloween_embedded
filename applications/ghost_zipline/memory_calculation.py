# Image 0
mem_adr = 0x0000C000
mem_size = 0x00077000
print(hex(mem_adr + mem_size))
print(f"Memory size image-0: {(mem_size)/1024:.0f} kB")
# Image 1
mem_adr = 0x00083000
mem_size = 0x00075000
print(hex(mem_adr + mem_size))
print(f"Memory size image-1: {(mem_size)/1024:.0f} kB")