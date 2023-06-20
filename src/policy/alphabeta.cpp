#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
std::vector<std::pair<State*, Move>> leaf_state;
Move alphabeta::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    if(state->game_state == WIN)    return state->legal_actions.back();
    Move BestMove;
    int val = -900000;
    bool existed_bestmove = false;
    for(auto it : state->legal_actions){
        
        int nxt_val = alphabeta::pruning(state->next_state(it), depth, state->player, -1000000, 1000000);
        if(nxt_val>val) {
            val = nxt_val;
            BestMove = it;
            existed_bestmove = true;
        }
    }
    if(existed_bestmove)    return BestMove;
    else return state->legal_actions[(rand()+depth)%state->legal_actions.size()];
}
int alphabeta::pruning(State* state, int depth, int player, int alpha, int beta){
    //alpha is the biggest child val of the state, 
    //since we choose the mini in oppn round, when alpha>beta, 
    //then there is no child val of the state can smaller than its sibling
    //beta is the smallest sibling val of the state, 
    //since we choose the max in self round , when beta>alpha,
    //then there is no child val of the state can bigger than its sibling
    
    if(depth == 1) return  state->evaluate(player);
    
    if(1-state->player == player){
        int val = -1000000;
        for(auto it : state->legal_actions){
            int tmp = pruning(state->next_state(it), depth-1, player, alpha, beta);
            if(tmp>val) val = tmp;
            if(val>alpha) alpha = val;
            if(alpha >= beta)   break;
        }
        return val;
    }
    else {
        int val = 1000000;
        for(auto it : state->legal_actions){
            int tmp = pruning(state->next_state(it), depth-1, player, alpha, beta);
            if(tmp<val)val = tmp;
            if(val<beta)    beta = val;
            if(beta<=alpha) break;
        }
        return val;
    }
    
}