#ifndef WORK_PLAN_H
#define WORK_PLAN_H

#endif // WORK_PLAN_H

// https://docs.microsoft.com/en-us/sql/tools/dta/tutorial-database-engine-tuning-advisor?redirectedfrom=MSDN&view=sql-server-ver15
// https://app.loadimpact.com/k6/runs/531042?compare=%5B%2223b08fba110ce87234ea01d967408924%22%2C%2205f7291fcb053635736401587e0594b6%22%2C%22edcb89ddbcbc9946999c35da4db6c43b%22%2C%2269ef410a4bbf6d9e9bd46e220f5d485b%22%2Cnull%5D&metrics=%5B%2223b08fba110ce87234ea01d967408924%22%2C%2205f7291fcb053635736401587e0594b6%22%2C%22edcb89ddbcbc9946999c35da4db6c43b%22%2C%2269ef410a4bbf6d9e9bd46e220f5d485b%22%2Cnull%5D
// TODO: --- 1 --- MultiThreading или асинхронные?
// TODO: --- 3 --- BackUp + Размер БД
// TODO: --- 4 --- Redirection нагрузки (LoadBalancing) синхронизация?
// TODO: --- 5 --- Нагрузочный тест + DB Tuning Adviser
// TODO: --- 6 --- Make keys in tables и ИНДЕКСЫ (для скорости)
// TODO: --- 100 --- ЧАТЫ
// TODO: --- 500 --- защита от атак (проверка результатов перед выдачей, ограничения)
// TODO: --- 100500 --- SSL

// БЛИЖАЙШИЕ:
 /* - СДЕЛАТЬ ОБЩУЮ ИНСТРУКЦИЮ С ПРИМЕРАМИ ЗАПРОСОВ (создать файл примеров)
 * - провести еще раз тест https://app.loadimpact.com (сначала надо перезарегиться на pagekite) */

// TODO: --- 7 --- Кики (условия: по времени и по загрузке железа и по количеству записей)
// - ПРОТЕСТИРОВАТЬ DELETE-функцию Image+comm+рекурсия(решено)
// - При удалении юзера удалять его голосования и друзей и может еще что
// - СКРИПТ НА ЗАПОЛНЕНИЕ БАЗЫ ДАННЫХ

// --- ВТОРОСТЕПЕННЫЕ ---
// - SQL инъекции добавить в Парс(code) + во все АПИ(bool) + системАПИ(bool)
// - добавить в Диспут оставшееся время, bool isAdvert
// - подумать над отправкой Диспута в архив
// - добавить в Юзер: кол-во отданных голосов (кол-во проголосованных споров), закладки(избранное)
// - разобраться с таймаутом
// - PUSH-уведомления, отправка писем на почту (e-mail spam?)

/* ГЛОБАЛЬНАЯ СИСТЕМА (задачи):
 * - перезапуск сервера, распределение
 * - очистка старых записей в базе данных
 * - UI с разными настройками, логи, статистика, он-лайн данные, список авторизованных юзеров и т.д.*/

/* "GET /disputes/getDisputeCount" (сначала получаем общее количество, затем выдаем группами)
 * "GET /disputes/getDispUuidsRange"
 * "GET /disputes/getDisputeByUuid" (полная, отправляем айди диспута)
 * "GET /answers/getAnswersByDisputeUuid" (отправляем айди диспута)
 * "GET /images/getImagesByPostUuid" (отправляем айди диспута)*/