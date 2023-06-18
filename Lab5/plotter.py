import matplotlib.pyplot as plt

data = []

with open("output.csv", "r") as file:
    for line in file:
        value = line.strip().split(',')
        data.append(value[0])
        print(data)

labels = ['1000', '2000', '3000', '4000', '5000']
plt.plot(labels, data,  marker='o', linestyle='')
plt.title("Number of comparisons while finding LCS regarding different seqnences length")
plt.xlabel('Sequence length')
plt.ylabel('No. of comparisons')
plt.show()