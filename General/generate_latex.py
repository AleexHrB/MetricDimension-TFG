import os
import sys
import re
import math
from scipy import stats

def read_file_to_list(filename):
    """Read a file and return its contents as a list of the last n lines, where n is declared in the filename."""
    # Extract n from the filename using regex
    match = re.search(r'(\d+)', filename)
    
    if not match:
        print(f"Warning: Could not determine 'n' value from filename {filename}. Skipping.")
        return []

    n = int(match.group(1))
    
    with open(filename, 'r') as f:
        lines = f.readlines()

    # Get the last n lines
    last_n_lines = lines[-n:]

    return [list(map(int, line.strip().split())) for line in last_n_lines if line.strip()]

def calculate_pvalues(files):

    
    file_data = {}  # Store filename and its corresponding data
    n_values = []   # Store all n values extracted from filenames

    for file in files:
        data = read_file_to_list(file)
        if data:
            n = len(data)
            n_values.append(n)
            file_data[file] = data

    max_columns = max(len(file_data[file]) for file in file_data)

    # Initialize a table with zeros
    table_data = {n: [0] * max_columns for n in n_values}
    
    # Populate the table data
    for file, data in file_data.items():
        n = len(data)
        for row_index, row in enumerate(data):
            table_data[n][row_index] = row[1]


    for data in table_data:
        print("n = " + str(data))
        print(table_data[data])
        print("Percentage " + str(table_data[data][math.floor(data/2) - 1] / sum(table_data[data])))

        #print("Lower bounds: " + str(math.ceil(math.log2(data)) - 1))
        #print("Upper Bound: " + str(math.floor(data/2)))


    



def generate_latex_table(files):
    """Generate the LaTeX table given a list of files."""
    
    file_data = {}  # Store filename and its corresponding data
    n_values = []   # Store all n values extracted from filenames

    for file in files:
        data = read_file_to_list(file)
        if data:
            n = len(data)
            n_values.append(n)
            file_data[file] = data

    max_columns = max(len(file_data[file]) for file in file_data)

    # Initialize a table with zeros
    table_data = {n: [0] * max_columns for n in n_values}
    
    # Populate the table data
    for file, data in file_data.items():
        n = len(data)
        for row_index, row in enumerate(data):
            table_data[n][row_index] = row[1]
    
    # Sort n values for table order
    sorted_n_values = sorted(n_values, reverse=True)

    # Generate the LaTeX table
    latex_code = "\\begin{sidewaystable}\n"
    latex_code += "    \\centering\n"
    latex_code += "    \\Large\n"
    latex_code += "    \\resizebox{\\textheight}{!}{\n"
    latex_code += "    \\begin{tabular}{|l|" + ("l|" * max_columns) + "}\n"
    latex_code += "    \\hline\n"
    latex_code += "         & " + " & ".join([f"$\\beta = {i + 1}$" for i in range(max_columns)]) + " \\\\ \\hline\n"
    for n in sorted_n_values:
        latex_code += f"        $n = {n}$ & " + " & ".join([f"${val}$" for val in table_data[n]]) + " \\\\ \\hline\n"
    latex_code += "    \\end{tabular}\n"
    latex_code += "    }\n"
    latex_code += "    \\caption{Your caption here} \n"
    latex_code += "\\end{sidewaystable} \n"

    latex_code += "\\begin{figure}[!htb] \n"
    
    """
    for i in sorted_n_values:
        latex_code += "\\begin{minipage}{0.48\\textwidth} \n"
        latex_code += "\\centering \n"
        latex_code += "\\begin{tikzpicture}\n"
        latex_code += "    \\begin{axis}[\n"
        latex_code += "        % Axis labels and titles\n"
        latex_code += "        xlabel={Metric Dimension},\n"
        latex_code += "        ylabel={Number of Graphs},\n"
        latex_code += "        % Bar settings\n"
        latex_code += "        ybar,\n"
        latex_code += "        ymin=0,\n"
        latex_code += "        bar width=0.5cm,\n"
        latex_code += f"        symbolic x coords={{{', '.join(map(str, [num+1 for num in range(len(table_data[i])) if table_data[i][num] != 0]))}}}, % X-axis labels\n"
        latex_code += "        xtick=data,         % Use symbolic labels\n"
        latex_code += "        cycle list={\n"
        latex_code += "            {fill=red!30, draw=red},\n"
        latex_code += "        },\n"
        latex_code += "        legend style={at={(0.5,-0.15)}, anchor=north,legend columns=-1},\n"
        latex_code += "        enlarge x limits={abs=0.8cm},\n"
        latex_code += "    ]\n"
        latex_code += "        % Add your data here\n"
        latex_code += "        \\addplot coordinates {\n"
        latex_code += "\n".join(f"({j+1},{table_data[i][j]})" for j in range(len(table_data[i])) if table_data[i][j] != 0)
        latex_code += "        };\n"
        latex_code += "    \\end{axis}\n"
        latex_code += "\\end{tikzpicture}\n"
        latex_code += f" \\caption{{Metric Dimension for $n = {i}}} \n"
        latex_code += f"\\label{{Fig:Data{i}}}"
        latex_code += "\\end{minipage}\\hfill \n"

    latex_code += "\\end{figure} \n"
    """
    return latex_code




def get_files_from_directory(directory_path):
    """Returns a list of .txt files from the provided directory."""
    return [os.path.join(directory_path, file) for file in os.listdir(directory_path) if file.endswith('.txt')]

if len(sys.argv) < 2:
    print("Please provide the directory path as an argument.")
    sys.exit(1)

directory_path = sys.argv[1]
files = get_files_from_directory(directory_path)
calculate_pvalues(files)
#latex_table = generate_latex_table(files)


