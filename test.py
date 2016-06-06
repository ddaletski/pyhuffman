import huffman
import matplotlib.pyplot as plt
import seaborn
filename = "test.txt"

string = open(filename).read()

original = []
compressed = []
decompressed = []

for i in range(3):
    comp = huffman.encode(string)
    decomp = huffman.decode(comp)
    print "equals" if decomp == string else "not equal"
    original.append(len(string))
    compressed.append(len(comp))
    decompressed.append(len(decomp))
    string = comp

for x, y, z in zip(original, compressed, decompressed):
    print "%7d, %7d, %4s%7d" % (x, y, '|', z)

#plt.plot(zip(original, compressed))
