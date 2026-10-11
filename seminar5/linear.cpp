// ============================================================================
// Семинар по алгоритмам: поиск в списке пользовательских идентификаторов.
// Задание: линейный поиск (перебор).
//
// Реализуйте функцию, помеченную TODO, в начале этого файла. Разбор параметров
// командной строки, генерация данных и замер времени уже готовы — менять их
// не нужно.
//
// Идентификатор — целое число uint64_t. Программа генерирует базу из N
// случайных ID и M запросов: часть запросов гарантированно присутствует в
// базе, остальные гарантированно отсутствуют. Замеряется время каждого этапа.
//
// Компиляция:
//     g++ -std=c++17 -O2 -o linear linear.cpp
// Запуск с параметрами по умолчанию:
//     ./linear
// Полный вид (показаны значения по умолчанию):
//     ./linear --size 1000000 --queries 1000 --seed 42 --hit-rate 0.5
// ============================================================================

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

namespace {

// ---------------------------------------------------------------------------
// Линейный поиск: последовательный проход по всему списку.
// ---------------------------------------------------------------------------
bool find_linear(const std::vector<uint64_t>& ids, uint64_t query) {
    for(uint64_t id : ids){
        if(query == id){
            return true;
        }
    }
    return false;
    
    throw std::runtime_error("find_linear: функция не реализована (см. TODO)");
}

constexpr uint64_t kDefaultSize = 1000000;
constexpr uint64_t kDefaultQueries = 1000;
constexpr uint64_t kDefaultSeed = 42;
constexpr double kDefaultHitRate = 0.5;

struct Options {
    uint64_t size = kDefaultSize;
    uint64_t queries = kDefaultQueries;
    uint64_t seed = kDefaultSeed;
    double hit_rate = kDefaultHitRate;
};

void print_usage(const char* prog) {
    std::cout << "Использование: " << prog << " [параметры]\n"
              << "  --size N       размер базы идентификаторов (по умолчанию " << kDefaultSize << ")\n"
              << "  --queries M    количество запросов (по умолчанию " << kDefaultQueries << ")\n"
              << "  --seed S       зерно генератора случайных чисел (по умолчанию " << kDefaultSeed << ")\n"
              << "  --hit-rate P   доля запросов, присутствующих в базе (по умолчанию " << kDefaultHitRate << ")\n"
              << "  --help         эта справка\n";
}

Options parse_args(int argc, char** argv) {
    Options opt;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        auto next_value = [&](const char* name) -> std::string {
            if (i + 1 >= argc) {
                std::cerr << "Не задано значение после " << name << "\n";
                std::exit(1);
            }
            return argv[++i];
        };
        try {
            if (arg == "--size") {
                opt.size = std::stoull(next_value("--size"));
            } else if (arg == "--queries") {
                opt.queries = std::stoull(next_value("--queries"));
            } else if (arg == "--seed") {
                opt.seed = std::stoull(next_value("--seed"));
            } else if (arg == "--hit-rate") {
                opt.hit_rate = std::stod(next_value("--hit-rate"));
            } else if (arg == "--help") {
                print_usage(argv[0]);
                std::exit(0);
            } else {
                std::cerr << "Неизвестный параметр: " << arg << "\n";
                print_usage(argv[0]);
                std::exit(1);
            }
        } catch (const std::exception& e) {
            std::cerr << "Некорректное значение параметра " << arg << ": " << e.what() << "\n";
            std::exit(1);
        }
    }
    if (opt.size == 0 || opt.hit_rate < 0.0 || opt.hit_rate > 1.0) {
        std::cerr << "Некорректные параметры: size должен быть > 0, hit-rate в диапазоне [0, 1]\n";
        std::exit(1);
    }
    return opt;
}

struct Dataset {
    std::vector<uint64_t> ids;
    std::vector<uint64_t> queries;
};

Dataset generate_data(const Options& opt) {
    std::mt19937_64 rng(opt.seed);
    Dataset data;
    data.ids.resize(static_cast<size_t>(opt.size));
    for (uint64_t& id : data.ids)
        id = rng();

    // Множество существующих ID нужно только чтобы «промахи» были гарантированно
    // отсутствуют в базе. Это служебная часть генерации, не измеряется как поиск.
    std::unordered_set<uint64_t> present;
    if (opt.hit_rate < 1.0)
        present.insert(data.ids.begin(), data.ids.end());

    // Ровно floor(M * hit_rate) запросов присутствуют в базе, остальные —
    // гарантированно отсутствуют; позиции «попаданий» перемешиваются.
    const size_t m = static_cast<size_t>(opt.queries);
    const size_t hits = static_cast<size_t>(static_cast<double>(m) * opt.hit_rate);
    std::vector<char> hit_query(m, 0);
    for (size_t i = 0; i < hits; ++i)
        hit_query[i] = 1;
    for (size_t i = m; i > 1; --i)
        std::swap(hit_query[i - 1], hit_query[rng() % i]);

    data.queries.reserve(m);
    for (size_t i = 0; i < m; ++i) {
        if (hit_query[i]) {
            data.queries.push_back(data.ids[rng() % static_cast<size_t>(opt.size)]);
        } else {
            uint64_t miss = rng();
            while (present.count(miss) != 0)
                miss = rng();
            data.queries.push_back(miss);
        }
    }
    return data;
}

using clock_type = std::chrono::steady_clock;

double elapsed_ms(clock_type::time_point start) {
    return std::chrono::duration<double, std::milli>(clock_type::now() - start).count();
}

}  // namespace

int run(const Options& opt) {

    const auto t_gen_start = clock_type::now();
    const Dataset data = generate_data(opt);
    const double gen_ms = elapsed_ms(t_gen_start);

    // Для линейного поиска подготовка индекса не требуется.
    const double prep_ms = 0.0;

    const auto t_search_start = clock_type::now();
    size_t found = 0;
    for (uint64_t query : data.queries) {
        if (find_linear(data.ids, query))
            ++found;
    }
    const double search_ms = elapsed_ms(t_search_start);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Алгоритм        : линейный поиск (перебор)\n";
    std::cout << "Параметры       : база = " << opt.size << " ID, запросов = " << opt.queries
              << ", hit-rate = " << opt.hit_rate << ", seed = " << opt.seed << "\n";
    std::cout << "Генерация данных: " << gen_ms << " мс\n";
    std::cout << "Подготовка      : " << prep_ms << " мс\n";
    std::cout << "Поиск           : " << search_ms << " мс";
    if (opt.queries > 0)
        std::cout << "  (" << search_ms * 1000.0 / static_cast<double>(opt.queries) << " мкс на запрос)";
    std::cout << "\nНайдено         : " << found << " из " << opt.queries << "\n";
    return 0;
}

int main(int argc, char** argv) {
    const Options opt = parse_args(argc, argv);
    try {
        return run(opt);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
}