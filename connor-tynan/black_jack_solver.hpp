#pragma once

#include <span>

#include "deffinitions.hpp"

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

public:
    chip_t get_bet();

    void take_payout(chip_t chips, std::span<const Card> dealer_cards);

    void on_reshuffle();

    BlackJackAction handle_hand(Card dealer_up_card, std::span<const Card> cards, BlackJackHandStatus status);
};
