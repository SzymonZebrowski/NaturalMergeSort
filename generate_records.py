import random
import argparse
import math

#generate_records.py -f file.txt -n 1000
parser = argparse.ArgumentParser()
parser.add_argument("-f", help="output for records", type=str)
parser.add_argument("-n", help="number of records to generate", type=int)
args = parser.parse_args()

print(args)
with open(args.f, 'w') as f:
    for i in range(args.n):
        a = float(random.uniform(0,100))
        b = float(random.uniform(0,100))
        c = float(random.uniform(0, math.pi))
        f.write(f"{a};{b};{c}\n")
