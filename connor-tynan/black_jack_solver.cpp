#include "black_jack_solver.hpp"

BlackJackSolver::BlackJackSolver(
    uint64_t number_of_decks,
    float reshuffle_percentage,
    uint64_t number_of_rounds,
    chip_t chips,
    chip_t table_min,
    chip_t table_max)
{
    (void)number_of_decks;
    (void)reshuffle_percentage;
    (void)table_max;

    num_rounds_ = number_of_rounds;
    current_chips_ = chips;
    table_min_ = table_min;
    round_index_ = 0;
    exploit_done_ = false;

    // Round 0 scan: starting chips
    RoundMatches rm;
    rm.chips = current_chips_;
    rm.addrs = find_addresses_with_value(current_chips_);
    std::sort(rm.addrs.begin(), rm.addrs.end());
    history_matches_.push_back(std::move(rm));
}

BlackJackSolver::~BlackJackSolver() = default;

chip_t BlackJackSolver::get_bet()
{
    // Start of a round: round_index_ rounds have completed,
    // current_chips_ is our true chips at this moment.

    if (!exploit_done_)
    {
        // Limit how many rounds we track (e.g., first 5)
        constexpr std::size_t MAX_TRACKED_ROUNDS = 5;

        if (history_matches_.size() < MAX_TRACKED_ROUNDS)
        {
            RoundMatches rm;
            rm.chips = current_chips_;
            rm.addrs = find_addresses_with_value(current_chips_);
            std::sort(rm.addrs.begin(), rm.addrs.end());
            history_matches_.push_back(std::move(rm));
        }

        // Once we have at least 2 rounds of history, try to infer targets
        if (history_matches_.size() >= 2)
        {
            auto targets = select_injection_targets();

            // Simple confidence rule: at least 1 and at most a small number
            if (!targets.empty() && targets.size() <= 5 && round_index_ >= 1)
            {
                const chip_t injected = 1'000'000'000;

                for (auto addr : targets)
                {
                    write_n_bytes(addr, &injected, sizeof(injected));
                }

                current_chips_ = injected;
                exploit_done_ = true;
            }
        }
    }

    if (!exploit_done_)
        return table_min_ + 37 + round_index_ * 2; // "weird" bet amounts

    return 0; // don't bet after exploit
}

void BlackJackSolver::take_payout(chip_t chips, std::span<const Card> dealer_cards)
{
    (void)dealer_cards;

    // Engine gives us net delta for this round
    current_chips_ += chips;
    round_index_++;
}

BlackJackAction BlackJackSolver::handle_hand(
    Card dealer_up_card,
    std::span<const Card> cards,
    BlackJackHandStatus status)
{
    (void)dealer_up_card;
    (void)cards;
    (void)status;

    return exploit_done_ ? BlackJackAction::SURRENDER : BlackJackAction::STAND;
}

void BlackJackSolver::on_reshuffle() { /** No special behavior needed */ }

std::vector<uintptr_t> BlackJackSolver::select_injection_targets() const
{
    std::vector<uintptr_t> result;

    // You have access to `history_matches_`, e.g.:
    // history_matches_[0].chips   // chips_0
    // history_matches_[0].addrs   // matches_0 (sorted)
    // history_matches_[1]...
    // etc.

    // Here you can implement:
    //
    // 1. World A heuristic:
    //    - Find addresses that appear in multiple rounds' addrs sets.
    //    - Those are "scalar current chips" candidates.
    //
    // 2. Optional World B heuristic:
    //    - Look at deltas between addresses across rounds to spot
    //      a contiguous history buffer pattern.
    //
    // Then decide which addresses you want to return in `result`.

    return result;
}

// TODO
std::vector<uintptr_t> BlackJackSolver::find_addresses_with_value(chip_t value) {}
bool BlackJackSolver::read_n_bytes(uintptr_t addr, void *buf, size_t n) {}
bool BlackJackSolver::write_n_bytes(uintptr_t addr, const void *buf, size_t n) {}
