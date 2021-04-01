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
    parents = []
    for line in kbfile:
        kb.append(line.split())
        parents.append(())
    prove = kb.pop()
    for literal in prove:
        if literal[0] == '~':
            kb.append([literal[1:]])
        else:
            kb.append(['~' + literal])
        parents.append(())
    return

if __name__=="__main__":
    main()
