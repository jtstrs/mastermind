#include "start_state.h"
#include "guess_state.h"
#include "../game_area.h"
#include "../abstract_user_request_acceptor.h"
#include "../guess_checker.h"

bool StartState::exec(std::shared_ptr<GameArea>& area, const std::unique_ptr<AbstractUserRequestAcceptor>& request_acceptor) {
    request_acceptor->writeMessage("Welcome to the game");
    request_acceptor->writeMessage("Write suggestions count");
    const std::size_t suggestions_count = request_acceptor->requestSuggestionsCount();
    request_acceptor->writeMessage("Write target sequence");
    const SequenceRow target_row = request_acceptor->requestTargetRow();

    auto guess_checker = std::make_unique<GuessChecker>(target_row);
    area = std::make_shared<GameArea>(suggestions_count, std::move(guess_checker));
    return true;
}

std::unique_ptr<AbstractMastermindState> StartState::nextState() {
    return std::make_unique<GuessState>();
}