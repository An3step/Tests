// MathUtils.swift

public class MathUtils {
    
    public static func isSquareMatrix(_ matrix: [[Int]]) -> Bool {
        let rows = matrix.count
        guard rows > 0 else { return false }
        return matrix.allSatisfy { $0.count == rows }
    }
    
    public static func rowSum(_ row: [Int]) -> Int {
        return row.reduce(0, +)
    }
    
    /// Вычисление суммы нечетных элементов строки
    public static func oddElementsSum(_ row: [Int]) -> Int {
        return row.filter { $0 % 2 != 0 }.reduce(0, +)
    }
    
    /// Сортировка матрицы по возрастанию суммы элементов строк
    public static func sortByRowSum(_ matrix: [[Int]]) -> [[Int]] {
        return matrix.sorted { rowSum($0) < rowSum($1) }
    }
    
    /// Сортировка матрицы по возрастанию суммы нечетных элементов строк
    public static func sortByOddElementsSum(_ matrix: [[Int]]) -> [[Int]] {
        return matrix.sorted { oddElementsSum($0) < oddElementsSum($1) }
    }
    
    // MARK: - Communication (Связь)
    
    /// Печать матрицы
    public static func printMatrix(_ matrix: [[Int]], title: String = "") {
        if !title.isEmpty {
            print(title)
        }
        for row in matrix {
            print(row.map { String($0) }.joined(separator: "\t"))
        }
        print()
    }
    
    /// Создание квадратной матрицы из входных данных
    public static func createMatrix(from input: String) -> [[Int]]? {
        let rows = input.components(separatedBy: ";")
        var matrix: [[Int]] = []
        
        for row in rows {
            let elements = row.components(separatedBy: ",").compactMap { Int($0.trimmingCharacters(in: .whitespaces)) }
            matrix.append(elements)
        }
        
        return isSquareMatrix(matrix) ? matrix : nil
    }
     
     // Сортировка матрицы по сумме нечетных элементов строк
     public static func sortMatrixByOddElementsSum(_ matrix: inout [[Int]]) {
         matrix.sort { oddElementsSum($0) < oddElementsSum($1) }
     }
     
     // Печать матрицы
     public static func printMatrix(_ matrix: [[Int]]) {
         for row in matrix {
             print(row.map { String($0) }.joined(separator: " "))
         }
     }
}
