prompt = "Enter the matrix size\n";
matrixSize = input(prompt);

while true
    G = rand(matrixSize, matrixSize, "gpuArray");
    if rank(G) == matrixSize; break; end %will be true nearly all the time
end

G2 = G' * G;

chr=int2str(matrixSize)

str = append("randomMatrix_",chr,".csv");

dlmwrite(str, G2, 'delimiter', ',', 'precision', 10);
