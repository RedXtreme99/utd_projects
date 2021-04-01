import sys

def main():
    if not len(sys.argv) == 2:
        print("Incorrect number of command line inputs")
        sys.exit(-1)
    try:
        kbfile = open(sys.argv[1], 'r').read().splitlines()
    except:
        print("File not found")
        sys.exit(-1)
    kb = []
    for line in kbfile:
        kb.append(line)
    prove = kb.pop()
    return

if __name__=="__main__":
    main()
