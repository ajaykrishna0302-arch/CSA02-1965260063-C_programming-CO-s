gcc -E billing_full.c -o billing_full.i   # 1. preprocess
gcc -S billing_full.c                     # 2. compile to assembly
gcc -c billing_full.c                     # 3. assemble to object
gcc -Wall -Wextra billing_full.c -o billing_full   # 4. link