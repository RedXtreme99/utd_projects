import sys
import copy

# If a clause contains both a literal and its complement, it is equivalent to True
def is_true(ls):
    ls1 = [x for x in ls if x[0] == '~']
    ls2 = [x for x in ls if x[0] != '~']
    for elem in ls1:
        if elem[1:] in ls2:
            return True
    return False

def is_redundant(kb, clause):
    clause.sort()
    if clause in kb:
        return True
    return False

def printkb(kb, parents):
    for i,value in enumerate(kb):
        outstr = ''
        outstr += str(i+1) + '. '
        if value != 'Contradiction':
            for literal in value:
                outstr += literal + ' '
        else:
            outstr += value + ' '
        outstr += '{'
        if parents[i][0] != 0:
            outstr += str(parents[i][0]) + ', ' + str(parents[i][1])
        outstr += '}'
        print(outstr)
    if kb[-1] == 'Contradiction':
        print('Valid')
    else:
        print('Fail')
    return


def main():
    # Check for knowledge base file as command line input
    if not len(sys.argv) == 2:
        print("Incorrect number of command line inputs")
        sys.exit(-1)

    # Read knowledge base lines
    try:
        kbfile = open(sys.argv[1], 'r').read().splitlines()
    except:
        print("File not found")
        sys.exit(-1)

    # Put each of the n-1 lines of the knowledge base into kb and put the 
    # negation of the last n line into kb. Each initial element has no parents
    kb = []
    sortedkb = []
    parents = []
    for line in kbfile:
        kb.append(line.split())
        parents.append((0,0))
    prove = kb.pop()
    parents.pop()
    for literal in prove:
        if literal[0] == '~':
            kb.append([literal[1:]])
        else:
            kb.append(['~' + literal])
        parents.append((0,0))
    for fact in kb:
        tmp = fact.copy()
        tmp.sort()
        sortedkb.append(tmp)

    # Attempt to resolve clauses iteratively
    done = False
    for i, entry in enumerate(kb):
        if done:
            break
        for j in range(0, i):
            resolve = False
            tmpclause = []
            for literal in entry:
                if literal[0] == '~':
                    if literal[1:] in kb[j]:
                        tmpclause = [term  for term in entry if term != literal] + [term for term in kb[j] if term != literal[1:]]
                        resolve = True
                        break
                else:
                    if ('~' + literal) in kb[j]:
                        tmpclause = [term for term in entry if term != literal] + [term for term in kb[j] if term != ('~' + literal)]
                        resolve = True
                        break
            if resolve:
                if not tmpclause:
                    kb.append('Contradiction')
                    parents.append((i+1,j+1))
                    done = True
                    break
                if is_true(tmpclause):
                    continue
                nodupes = []
                [nodupes.append(x) for x in tmpclause if x not in nodupes]
                if is_redundant(sortedkb, copy.deepcopy(nodupes)):
                    continue
                kb.append(nodupes)
                parents.append((i+1,j+1))
                tmp = nodupes.copy()
                tmp.sort()
                sortedkb.append(tmp)
    printkb(kb, parents)
    return

if __name__=="__main__":
    main()
