//
//  main.swift
//  Task2
//
//  Created by kit on 16.06.25.
//

import Foundation

func main() {
    let russianString = "Привет это тестовая строка для проверки работы программы"
    
    let averageLength = StringUtils.averageWordLength(russianString)
    print("Средняя длина слов: \(averageLength)")
    
    let count = StringUtils.countWordsWithMoreThanThreeVowels(russianString)
    print("Количество слов с более чем 3 гласными: \(count)")}

main()
