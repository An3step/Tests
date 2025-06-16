
// main.swift (version 1)

import Foundation

//print("Введите квадратную матрицу в формате: 1,2,3;4,5,6;7,8,9")
//guard let input = readLine() else {
  //  fatalError("Ошибка чтения ввода")
//}

//guard let matrix = MathUtils.createMatrix(from: input) else {
  //  fatalError("Введена некорректная квадратная матрица")
//}

//let matrix = [
    //[4, 5, -6],
    //[1, 2, 3],
  //  [7, 8, 9]
//]

//print("\nИсходная матрица:")
//MathUtils.printMatrix(matrix)

//let sortedMatrix = MathUtils.sortByRowSum(matrix)

//print("\nМатрица, отсортированная по возрастанию сумм элементов строк:")
//MathUtils.printMatrix(sortedMatrix)

import Foundation

func main() {
    // Пример квадратной матрицы
    var matrix = [
        [4, 3, 2],
        [1, 5, 6],
        [0, 8, 1]
    ]
    
    print("Исходная матрица:")
    MathUtils.printMatrix(matrix)
    
    // Сортировка по сумме нечетных элементов
    MathUtils.sortMatrixByOddElementsSum(&matrix)
    print("\nМатрица после сортировки по сумме нечетных элементов:")
    MathUtils.printMatrix(matrix)
}

main()
