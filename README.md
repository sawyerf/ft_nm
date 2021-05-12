https://stackoverflow.com/questions/15225346/how-to-display-the-symbols-type-like-the-nm-command

| Tag | Condition | Description |
|:---:|-----------|-------------|
| A   | st_shndx == ABS | The symbol’s value is absolute, and will not be changed by further linking. |
| B   | .bss      | The symbol is in the uninitialized data section (known as BSS). |
| C   | st_shndx == COMMON | The symbol is common. Common symbols are uninitialized data. When linking, multiple common symbols may appear with the same name. If the symbol is defined anywhere, the common symbols are treated as undefined references. |
| D   | .data .dynamic | The symbol is in the initialized data section. |
| G   |           | The symbol is in an initialized data section for small objects. Some object file formats permit more efficient access to small data objects, such as a global int variable as opposed to a large global array. |
| I   |           | The symbol is an indirect reference to another symbol. This is a GNU extension to the a.out object file format which is rarely used. |
| N   |           | The symbol is a debugging symbol. |
| R   | .rodata   | The symbol is in a read only data section. |
| S   |           | The symbol is in an uninitialized data section for small objects. |
| T   | .text     | The symbol is in the text (code) section. |
| u   | bind == GNU\_UNIQUE |  |
| U   | st_ndx == UNDEF | The symbol is undefined. |
| V   | bind == WEAK && type == OBJECT | The symbol is a weak object. When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is used with no error. When a weak undefined symbol is linked and the symbol is not defined, the value of the weak symbol becomes zero with no error. |
| W   | bind == WEAK | The symbol is a weak symbol that has not been specifically tagged as a weak object symbol. When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is used with no error. When a weak undefined symbol is linked and the symbol is not defined, the value of the symbol is determined in a system-specific manner without error. On some systems, uppercase indicates that a default value has been specified. |
| -   |           | The symbol is a stabs symbol in an a.out object file. In this case, the next values printed are the stabs other field, the stabs desc field, and the stab type. Stabs symbols are used to hold debugging information. |
| ?   |           | The symbol type is unknown, or object file format specific.  |
