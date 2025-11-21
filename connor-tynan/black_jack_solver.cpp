#include "black_jack_solver.hpp"

BlackJackSolver::BlackJackSolver(
    uint64_t number_of_decks,
    float reshuffle_percentage,
    uint64_t number_of_rounds,
    chip_t chips,
    chip_t table_min,
    chip_t table_max)
{
}

BlackJackSolver::~BlackJackSolver() {}

chip_t BlackJackSolver::get_bet() { return 0; }

BlackJackAction
    BlackJackSolver::handle_hand(Card dealer_up_card, std::span<const Card> cards, BlackJackHandStatus status)
{
    return BlackJackAction::STAND;
}

void BlackJackSolver::take_payout(chip_t chips, std::span<const Card> dealer_cards) {}

void BlackJackSolver::on_reshuffle() {}
