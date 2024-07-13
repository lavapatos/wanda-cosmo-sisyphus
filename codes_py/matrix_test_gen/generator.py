import random
import os

output_dir = '..\\..\\codes_cpp\\WandaCosmoApocalypse\\tests\\96x96'

os.makedirs(output_dir, exist_ok=True)

for i in range(100):
    output_file = os.path.join(output_dir, f'96x96_matrix_{i}.txt')

    with open(output_file, 'w') as f:
        for _ in range(96):
            row = ','.join(str(random.randint(0, 2)) for _ in range(96))
            f.write(row + '\n')

    print(f'testecase {i}: {output_file} en {output_dir}.')