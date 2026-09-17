import PyPDF2

merger = PyPDF2.PdfMerger()
files = ['lab_1.pdf', 'lab_2.pdf', 'lab_3.pdf']

for pdf in files:
    merger.append(pdf)

merger.write("merged_output.pdf")
merger.close()