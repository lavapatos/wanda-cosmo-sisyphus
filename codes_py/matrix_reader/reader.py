import csv

csv_file = '..\\..\\codes_cpp\\WandaCosmoApocalypse\\tests\\64x64\\64x64_matrix_0.txt'

DeadCount = 0
WandaCount = 0
CosmoCount = 0

with open(csv_file, 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        numbers = list(map(int, row))
        
        DeadCount += numbers.count(0)
        WandaCount += numbers.count(1)
        CosmoCount += numbers.count(2)

print(f'Dead: {DeadCount}')
print(f'Wandas: {WandaCount}')
print(f'Cosmos: {CosmoCount}')
print(f'Total: {DeadCount+WandaCount+CosmoCount}')