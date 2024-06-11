import random
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-n", "--keynum", dest="keynum", action="store")          # extra value
parser.add_argument("-l", "--keylen", dest="keylen", action="store")
parser.add_argument("-p", "--path" , dest="outputpath", action="store")
args = parser.parse_args()

keynum = int(args.keynum)
keylen = int(args.keylen)
output = './'+args.outputpath


Capital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
Small = "abcdefghijklmnopqrstuvwxyz"
Number = "123456789"

key_list = ""
for i in  range(keynum):
    key = ["" for j in range(keylen)]
    try:
        C_N = random.randrange(int(keylen*0.2),int(keylen*0.4))
        S_N = random.randrange(int(keylen*0.2),int(keylen*0.4))
    except:
        C_N = random.randrange(int(keylen*0.2),int(keylen*0.4+1))
        S_N = random.randrange(int(keylen*0.2),int(keylen*0.4+1))
    for j in range(C_N):
        idx = random.randrange(keylen)
        while key[idx] != "":
            idx = random.randrange(keylen)
        key[idx] = random.choice(Capital)
    for j in range(S_N):
        idx = random.randrange(keylen)
        while key[idx] != "":
            idx = random.randrange(keylen)
        key[idx] = random.choice(Small)
    for j in range(keylen-C_N-S_N):
        idx = random.randrange(keylen)
        while key[idx] != "":
            idx = random.randrange(keylen)
        key[idx] = random.choice(Number)
    key_list = key_list+''.join(key)+'\n'
key_list = key_list[:-1]

if output[-1] == '/':
    output = output + "keys.txt"
else:
    output = output+"/keys.txt"

f = open(output,'w')
f.write(key_list)
f.close()
