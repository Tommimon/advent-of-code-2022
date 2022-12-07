import copy


class TreeNode(object):
    def __init__(self, name='root', children=None, parent=None, size=0):
        self.name = name
        self.parent = parent
        self.children = []
        self.size = size
        if children is not None:
            for child in children:
                self.add_child(child)

    def is_root(self):
        if self.parent is None:
            return True
        else:
            return False

    def add_child(self, node):
        node.parent = self
        assert isinstance(node, TreeNode)
        self.children.append(node)
        if (node.name.split())[0].isdigit():
            self.size += int((node.name.split())[0])
            self.update(int((node.name.split())[0]))

    def update(self, quantity):
        if not self.is_root():
            self.parent.size += quantity
            self.parent.update(quantity)

    def check_path(self, path2):
        if self.parent is None and len(path2) == 0:
            return True
        elif self.parent is not None and len(path2) != 0:
            if self.parent.name == path2[-1]:
                path2.pop()
                return self.parent.check_path(path2)
        return False


class Tree:
    def __init__(self):
        self.root = None
        self.nodes = []

    def insert(self, node, parent):
        if parent is not None:
            parent.add_child(node)
        else:
            if self.root is None:
                self.root = node
        self.nodes.append(node)
        if (node.name.split())[0].isdigit():
            self.root.size += int((node.name.split())[0])

    def search(self, path1):
        index = -1
        for n in self.nodes:
            index += 1
            temp = copy.deepcopy(path1)
            temp.pop()
            if n.name == path1[-1] and n.check_path(temp):
                break
        if index == len(self.nodes) - 1:
            return -1
        else:
            return index


tree = Tree()
tree.insert(TreeNode('root'), None)
max = 100000
commands = ["$ cd /", "$ cd ..", "$ ls"]
path = []
i = 0
with open('input.txt') as file:
    input = file.readlines()
while i < len(input):
    input[i] = input[i].replace("\n", '')
    if input[i] == commands[0]:
        path.clear()
    elif input[i] == commands[1]:
        path.pop()
    elif input[i][0] == '$' and input[i] not in commands:
        path.append("dir " + input[i][5:])
    elif input[i] == commands[2]:
        i += 1
        while i < len(input) and input[i][0] != '$':
            input[i] = input[i].replace("\n", '')
            if len(path) != 0:
                tree.insert(TreeNode(input[i]), tree.nodes[tree.search(path)])
            else:
                tree.insert(TreeNode(input[i]), None)
            i += 1
        i -= 1
    i += 1
part_1 = sum(nd.size for nd in tree.nodes if nd.size <= max)
total_space = 70000000
needed_space = 30000000
used_space = tree.root.size
available_space = total_space - used_space
needed_space -= available_space
part_2 = tree.root.size
for nd in tree.nodes:
    if needed_space <= nd.size < part_2:
        part_2 = nd.size
print(part_1)
print(part_2)
