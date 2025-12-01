#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Неполное определение структуры хеш-таблицы (реализуйте её самостоятельно).
 */
typedef struct hash_table hash_table_t;


/**
 * @brief Создаёт новую хеш-таблицу заданной ёмкости.
 *
 * @param capacity Количество бакетов в таблице
 * @return Указатель на созданную хеш-таблицу или NULL при ошибке
 */
hash_table_t *ht_init(size_t capacity);

/**
 * @brief Вставляет пару (ключ, значение) в хеш-таблицу.
 * Если элемент с таким ключом уже существует, значение перезаписывается.
 *
 * @param ht Указатель на хеш-таблицу
 * @param key Ключ (целое число)
 * @param value Значение (целое число)
 * @return true, если вставка выполнена успешно; false при ошибке (например, нехватка памяти)
 */
bool ht_insert(hash_table_t *ht, int32_t key, int32_t value);

/**
 * @brief Ищет элемент по ключу в хеш-таблице.
 *
 * @param ht Указатель на хеш-таблицу
 * @param key Ключ, который нужно найти
 * @param out_value Указатель, куда будет записано найденное значение
 * @return true, если элемент найден; false, если ключ отсутствует
 */
bool ht_search(hash_table_t *ht, int32_t key, int32_t *out_value);

/**
 * @brief Освобождает всю память, занятую хеш-таблицей.
 *
 * @param ht Указатель на хеш-таблицу
 */
void ht_free(hash_table_t *ht);

#endif