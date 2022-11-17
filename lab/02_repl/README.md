### TODO:

Create a REPL to let you read and write RP2040 registers from a console. You should be able to:
- select any 32-bit address to read/write (even if not a valid RP2020 address)
- read/write any 32-bit value to this address
- read/write using any of the atomic bit-setting aliases and a 32-bit mask

### Description
1. We first read the gpio boot put register using the register read function.
```
register_read(QTPY_GPIO_PIN_REG)
```
2. We then write the new 32 bit value to the register and mask it with the previous value
```
register_write((QTPY_GPIO_PIN_REG), (register_read(QTPY_GPIO_PIN_REG)|value));
```
3. We finally print the new value.
