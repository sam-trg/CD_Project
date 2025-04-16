import re
import sys

def indent_c_to_c(lines):
    output = []
    indent_stack = [0]

    for i, line in enumerate(lines):
        stripped = line.strip()
        if not stripped or stripped.startswith("//"):
            output.append(line)
            continue

        current_indent = len(line) - len(line.lstrip(' '))
        prev_indent = indent_stack[-1]

        while current_indent < prev_indent:
            output.append(' ' * indent_stack[-1] + '}')
            indent_stack.pop()
            prev_indent = indent_stack[-1]

        if stripped.endswith(':'):
            output.append(' ' * current_indent + stripped[:-1] + ' {')
            indent_stack.append(current_indent + 4)
        else:
            output.append(line)

    while len(indent_stack) > 1:
        output.append(' ' * indent_stack[-1] + '}')
        indent_stack.pop()

    return output

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python convert.py <input.ic>")
        sys.exit(1)

    with open(sys.argv[1], 'r') as f:
        lines = f.readlines()

    converted = indent_c_to_c(lines)

    output_file = sys.argv[1].replace('.ic', '.c')
    with open(output_file, 'w') as f:
        f.write('\n'.join(converted))
