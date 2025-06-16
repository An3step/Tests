//
//  StringUtils.swift
//  Task2
//
//  Created by kit on 16.06.25.
//

public class StringUtils {
    
    // Разделение строки на слова
    public static func splitIntoWords(_ str: String) -> [String] {
        return str.components(separatedBy: " ")
    }
    
    // Вычисление средней длины слов
    public static func averageWordLength(_ str: String) -> Double {
        let words = splitIntoWords(str)
        guard !words.isEmpty else { return 0 }
        let totalLength = words.reduce(0) { $0 + $1.count }
        return Double(totalLength) / Double(words.count)
    }
    
    public static func countVowels(in word: String) -> Int {
        let vowels: Set<Character> = ["а", "е", "ё", "и", "о", "у", "ы", "э", "ю", "я",
                                     "А", "Е", "Ё", "И", "О", "У", "Ы", "Э", "Ю", "Я"]
        return word.filter { vowels.contains($0) }.count
    }
    
    // Подсчет слов с более чем 3 гласными
    public static func countWordsWithMoreThanThreeVowels(_ str: String) -> Int {
        let words = splitIntoWords(str)
        return words.filter { countVowels(in: $0) > 3 }.count
    }
}
