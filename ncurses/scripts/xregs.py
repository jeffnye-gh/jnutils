import time
import random
# Test program to generate random updates to xregs data
# and write a log file

def generate_substrings():
    # Generate a random number of substrings between 2 and 4
    num_substrings = random.randint(2, 4)
    substrings = []

    for _ in range(num_substrings):
        # Generate a number between 0 and 31
        x_number = random.randint(0, 31)
        # Generate a 16-digit hex value prefixed with "0x"
        hex_value = f"0x{random.randint(0, 0xFFFFFFFFFFFFFFFF):016X}"
        # Create the substring in the format "X<number>:<hex_value>"
        substrings.append((f"X{x_number}", hex_value))

    return substrings

def main():
    # Internal dictionary to keep track of X0 to X31 contents, initialized to "0x----------------"
    xregs = {f"X{i}": "0x----------------" for i in range(32)}
    count = 0
    first = True

    while True:
        # Generate random updates
        new_values = generate_substrings()

        # Update the internal dictionary with the new values
        for key, value in new_values:
            xregs[key] = value

        # Write the current contents of the internal dictionary to "results/py_results.txt"
        if(first == False):
          with open("results/py_results.txt", "a") as golden_file:
              golden_file.write(f"count: {count}\n")
              for key, value in xregs.items():
                  golden_file.write(f"{key}:{value}\n")
              golden_file.flush()
        first = False

        # Write only the newly generated values to "data/xregs.txt"
        with open("data/xregs.txt", "w") as xregs_file:
            for key, value in new_values:
                print(f"{key}:{value}")
                xregs_file.write(f"{key}:{value}\n")
            xregs_file.flush()

        # Print status
        print(f"Wrote to results/py_results.txt and data/xregs.txt, count: {count}")
        count += 1
        time.sleep(5)  # Sleep for 5 seconds

if __name__ == "__main__":
    main()

