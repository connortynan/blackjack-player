#pragma once

#include <span>
#include <vector>
#include <cstdint>
#include <algorithm>

#include "shared/deffinitions.hpp"

class BlackJackSolver
{
public:
    BlackJackSolver(
        uint64_t number_of_decks,
        float reshuffle_percentage,
        uint64_t number_of_rounds,
        chip_t chips,
        chip_t table_min,
        chip_t table_max);

    ~BlackJackSolver();

    chip_t get_bet();
    void take_payout(chip_t chips, std::span<const Card> dealer_cards);
    void on_reshuffle();
    BlackJackAction handle_hand(
        Card dealer_up_card,
        std::span<const Card> cards,
        BlackJackHandStatus status);

private:
    // minimal state
    chip_t current_chips_{0};
    chip_t table_min_{0};
    uint64_t num_rounds_{0};
    uint64_t round_index_{0}; // completed rounds so far
    bool exploit_done_{false};

    // Per-round scan results
    struct RoundMatches
    {
        chip_t chips;                 // chip total at this round start
        std::vector<uintptr_t> addrs; // sorted addresses with that value
    };
    std::vector<RoundMatches> history_matches_;

    std::vector<uintptr_t> select_injection_targets() const;

    // memory access helpers
    std::vector<uintptr_t> find_addresses_with_value(chip_t value);
    bool read_n_bytes(uintptr_t addr, void *buf, size_t n);
    bool write_n_bytes(uintptr_t addr, const void *buf, size_t n);

};
