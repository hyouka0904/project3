#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
std::vector<std::pair<State*, Move>> leaf_state;
Move minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    if(state->game_state == WIN)    return state->legal_actions.back();
    Move BestMove;
    int val = -900000;
    bool existed_bestmove = false;
    for(auto it : state->legal_actions){
        
        int nxt_val = minimax::minimax_val(state->next_state(it), depth, state->player);
        if(nxt_val>val) {
            val = nxt_val;
            BestMove = it;
            existed_bestmove = true;
        }
    }
    if(existed_bestmove)    return BestMove;
    else return state->legal_actions[(rand()+depth)%state->legal_actions.size()];
}
int minimax::minimax_val(State* state, int depth, int player){
    
    if(depth == 1) return  state->evaluate(player);
    
    if(1-state->player == player){//judge the one just moved the chess
        int val = -900000;
        for(auto it : state->legal_actions){
            int nxt_val = minimax::minimax_val(state->next_state(it),  depth-1, player);
            if(nxt_val>val) val = nxt_val;
        }
        return val;
    }
    else {
        int val = 900000;
        for(auto it : state->legal_actions){
            int nxt_val = minimax::minimax_val(state->next_state(it), depth-1, player);
            if(nxt_val<val) val = nxt_val;
        }
        return val;
    }
    
}