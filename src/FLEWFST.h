/**
 * \class FLEWFST
 * \file FLEWFST.h
 *
 * \brief Provide a class for a Weighted Finite State Transducer (WFST)
 *
 * This class provides the data structures and methods for a WFST
 * that contains a representation of a grammar (CFG, PCFG, or similar) with
 * weights over transitions in the CFG-right-hand-side symbols.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/02/23 14:25:00
 *
 * \date Created on: Tue Feb 23 14:25:00 2016
 *
 * \copyright Copyright 2016 by Damir Cavar
 *
 * \license{Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.}
 *
 * \note This needs some optimization.
 *
 * \bug None
 */


#ifndef GRAMMARTEST_FLEWFST_H
#define GRAMMARTEST_FLEWFST_H

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <functional>


using namespace std;


/*! An arc_val type.
    It holds the to-state ID, the output symbol ID, and the weight.
 */
typedef tuple<unsigned long, unsigned long, double> arc_val;

/*! An arc_key type.
    It holds the from-state ID, the input symbol ID.
 */
typedef pair<unsigned long, unsigned long> arc_key;

// transition type for the transition hash-map
typedef map<arc_key, set<arc_val>> transitionType;

// fwtransition type: symbols leaving a state
// key = state, value = set of symbols leaving this state
typedef map<unsigned long, set<unsigned long>> fwtransitionsType;


//! A Weighted Finite State Transducer (WFST) class for FLE.
/*!
  This <a href="https://en.wikipedia.org/wiki/Finite_state_transducer">WFST</a> class serves as the grammar storage
  for the XLE-based <a href="https://en.wikipedia.org/wiki/Lexical_functional_gratuple<unsigned long, unsigned int, double>mmar">Lexical Functional Grammars</a>
  (<a href="https://en.wikipedia.org/wiki/Lexical_functional_grammar">LFG</a>), as well as for plain grammars using
  the <a href="https://en.wikipedia.org/wiki/Context-free_grammar">Context Free</a>
  (<a href="https://en.wikipedia.org/wiki/Context-free_grammar">CFG</a>) or
  <a href="https://en.wikipedia.org/wiki/Stochastic_context-free_grammar">Probabilisitic-context Free Grammar</a>
  (<a href="https://en.wikipedia.org/wiki/Stochastic_context-free_grammar">PCFG</a>) frameworks or formalisms.

  This <a href="https://en.wikipedia.org/wiki/Finite_state_transducer">WFST</a> associates input symbol sequences
  (right-hand-sides of the grammar backbone) with the left-hand-side symbol. One can associate a weight with any such
  transition. In addition to this common <a href="https://en.wikipedia.org/wiki/Finite_state_transducer">WFST</a>
  definition, this class allows to specify functions for every transition that either return an additional value for
  the output tape, None, or true.

  These functions are used as filters that block a transition, or return additional data, e.g. a unified feature
  <a href="https://en.wikipedia.org/wiki/Feature_structure">AVM</a>, a Monotonicity Calculus result, and so on.

  Created by <a href="https://linguistlist.org/people/damir_cavar.html">Damir Cavar</a> on 2/23/16.

  See for more details the <a href="http://gorilla.linguistlist.org/fle/">FLE project homepage</a>.
*/
class FLEWFST {
public:
    //! A constructor.
    /*! The default constructor does not contain any special code yet. */
    FLEWFST();

    //! A destructor.
    /*! The default destructor does not contain any special code yet. */
    ~FLEWFST();

    //! Adding a state to the WFST.
    /*!
      \param state An unsigned long argument as the new state ID.
      Adds a new state to the WFST with a concrete numeric state ID.
    */
    unsigned long addState(const unsigned long state);

    //! Adding a state to the WFST.
    /*!
      \return an unsigned long argument.
      Adds a new state to the WFST and returns its ID.
    */
    unsigned long addState();

    //! Removing a state from the WFST.
    /*!
      \param state The state to be removed.
      Removes a state from the WFST.
    */
    void removeState(const unsigned long state);

    //! Declaring a state to be *final*.
    /*!
      \param state The unsigned long ID of the state that is declared as final.
      Sets the state with ID as final state in the WFST.
    */
    void setFinalState(const unsigned long state);

    //! Declaring a state to not be *final*.
    /*!
      \param state The unsigned long ID of the state that is declared as not final.
      Removes the state with ID from the set of final states in the WFST.
    */
    void unsetFinalState(const unsigned long state);

    //! Declaring a state to be the *start state*.
    /*!
      \param state The unsigned long ID of the state that is declared to be the start state.
      Sets the the state with ID as the start state in the WFST. If there is another state that
      is declared start state, this will be reset. There can only be one start state in this
      type of WFST.
    */
    void setStartState(const unsigned long state);

    //! Adding a symbol to the mapping list.
    /*!
      \param symbol The string of a symbol.
      \return The unsigned long ID of the symbol in the symbol mapping table.
      Adds a symbol to the symbol mapping table and returns the corresponding ID.
      If the string symbol is already present in the mapping table, it's corresponding value will be returned.
      If it is not in the mapping table, it will be added, a symbol ID will be assigned to it and it's value
      returned.
    */
    unsigned long addSymbol(const string symbol, bool terminal);

    // unsigned long addSymbol(const string symbol);

    bool isTerminal(const unsigned long symbol_id);

    //! Retrieving a symbol ID from a string.
    /*!
      \param symbol The string of a symbol.
      \return The unsigned long ID of the symbol in the symbol mapping table.
      Returns the symbol ID for a string.
    */
    unsigned long getSymbolID(const string symbol);

    //! Retrieving a symbol string from an ID.
    /*!
      \param symbol The symbol ID.
      \return The string of the symbol in the symbol mapping table.
      Returns the string for the corresponding symbol ID.
    */
    string getSymbol(const unsigned long symbol);

    //! Add an arc for state, input and weight.
    /*!
      \param from The transition from-state as unsigned long.
      \param symbol The input symbol ID as unsigned long.
      \param weight The weight as double.
      \return The target state ID as unsigned long.
      Adds a transition (arc) to the WFST.
    */
    unsigned long addArc(const unsigned long from,
                         const unsigned long symbol,
                         const double weight);

    //! Add an arc for state with weight and epsilon transition.
    /*!
       \param from The from-state ID as unsigned long.
       \param weight The weight as double.
       \return The new state as unsigned long,
      Adds a transition (arc) to the WFST. This member method returns a newly created state ID for a transition
      with a specific weight from the given state ID as an epsilon transition.
    */
    unsigned long addArc(const unsigned long from,
                         const double weight);

    //! Add an arc for state and input symbol.
    /*!
       \param from The from-state ID as unsigned long
       \param symbol The input symbol ID as unsigned long.
       \return The new state as unsigned long
      Adds a transition (arc) to the WFST. This member method returns a newly created state ID for a transition
      with a specific weight from the given state ID as an epsilon transition.
    */
    unsigned long addArc(const unsigned long from,
                         const unsigned long symbol);

    //! Add an arc for state, input, output, and weight.
    /*!
      \param from The transition from-state as unsigned long.
      \param symbol The input symbol ID as unsigned long.
      \param outsymbol The output symbol ID as unsigned long.
      \param weight The weight as double.
      \return The target state ID as unsigned long.
      Adds a transition (arc) to the WFST.
    */
    unsigned long addArc(const unsigned long from,
                         const unsigned long symbol,
                         const unsigned long outsymbol,
                         const double weight);

    //! Add an arc for state, input, output, and weight.
    /*!
      \param from The transition from-state as unsigned long.
      \param to The transition to-state as unsigned long.
      \param symbol The input symbol ID as unsigned long.
      \param outsymbol The output symbol ID as unsigned long.
      \param weight The weight as double.
      \return The target state ID as unsigned long.
      Adds a transition (arc) to the WFST.
    */
    unsigned long addArc(const unsigned long from,
                         const unsigned long to,
                         const unsigned long symbol,
                         const unsigned long outsymbol,
                         const double weight);

    //! Remove an arc for state, input, output, and weight.
    /*!
      \param from The transition from-state as unsigned long.
      \param symbol The input symbol ID as unsigned long.
      \param outsymbol The output symbol ID as unsigned long.
      \param weight The weight as double.
      Removes a transition (arc) to the WFST.
    */
    void delArc(const unsigned long from,
                const unsigned long symbol,
                const unsigned long outsymbol,
                const double weight);

    //! Remove an arc for state, input and weight.
    /*!
      \param from The transition from-state as unsigned long.
      \param symbol The input symbol ID as unsigned long.
      \param weight The weight as double.
      Removes a transition (arc) to the WFST.
    */
    void delArc(const unsigned long from,
                const unsigned long symbol,
                const double weight);

    //! Remove an arc for state with weight and epsilon transition.
    /*!
       \param from The from-state ID as unsigned long.
       \param weight The weight as double.
      Removes a transition (arc) to the WFST. This member method returns a newly created state ID for a transition
      with a specific weight from the given state ID as an epsilon transition.
    */
    void delArc(const unsigned long from,
                const double weight);

    //! Remove an arc for state and input symbol.
    /*!
       \param from The from-state ID as unsigned long
       \param symbol The input symbol ID as unsigned long.
      Removes a transition (arc) to the WFST. This member method returns a newly created state ID for a transition
      with a specific weight from the given state ID as an epsilon transition.
    */
    void delArc(const unsigned long from,
                const unsigned long symbol);

    //! Change the weight of an arc.
    /*!
       \param key The from-state ID and symbol ID.
       \param val The new state, output symbol and original weight.
       \param weight The new weight.
      Sets the weight for a transition (arc) in the WFST.
    */
    void setWeight(arc_key key,
                   arc_val val,
                   const double weight);


    //! Add function to an arc.
    /*!
       \param key The from-state ID and symbol ID.
       \param val The new state, output symbol and original weight.
       \param fct A pointer to a function.
      Adds a function to a transition (arc) in the WFST.
    */
    void addFunction(arc_key key,
                     arc_val val,
                     const double fct);

    //! Clears the entire WFST defintion.
    /*!
      Clears all containers in the WFST representations.
    */
    void clear();

    //! Minimizes the WFST.
    /*!
      Minnimization of the WFST.
    */
    void minimize();

    //! Returns the DOT representation of the WFST as a string.
    /*!
      The DOT representation as a string.
    */
    string getDOT();

    //! Returns the SVG representation of the WFST as a string.
    /*!
      The SVG representation as a string.
    */
    string getSVG();

    //! Returns the PDF representation of the WFST as a string.
    /*!
      The PDF representation as a string.
    */
    string getPDF();

    /*! The set of states. States are of type unsigned long. */
    set<unsigned long> states_set;

    /*! The set of final states. States are of type unsigned long. */
    set<unsigned long> finalstates_set;

    bool isFinalState(unsigned long);

    unsigned long start_state;  /*!< The start state. Only one start state of type unsigned long. */

    //! transitions is a map that holds transition information (arcs).
    /*! key: current state, input symbol
        value: vector of tuples: new state, output, weight
        add to value a vector of functions to call: unification that returns a new f-structure, Monotonicity...
        Non-deterministic data structure, it is determinisitic, if the value vector is of size = 1 for all arcs
    */
    transitionType transitions;

    //! revtransitions is a map that holds transition information (arcs).
    /*! key: current state, input symbol
        value: vector of tuples: new state, output, weight
        add to value a vector of functions to call: unification that returns a new f-structure, Monotonicity...
        Non-deterministic data structure, it is determinisitic, if the value vector is of size = 1 for all arcs
    */
    map<unsigned long, set<arc_key>> revtransitions;

    //! fwtransitions is a map that holds transition information (arcs).
    /*! key: current state
        value: set of symbols that transit from this state
    */
    fwtransitionsType fwtransitions;

    //! symbol_map is a map that holds symbol string mappings to numeric IDs.
    /*!
       Keys in the map are the symbol strings and the corresponding numeric ID is the value of type unsigned long.
       The reverse map is #symbol_id_map. The bool value marks terminals or symbols, true = terminal, false (default) symbol.
    */
    map<string, pair<unsigned long, bool>> symbol_map;

    //! terminal_map is a map that holds terminal string mappings to numeric IDs.
    /*!
       Keys in the map are the terminal strings and the corresponding numeric ID is the value of type unsigned long.
       The reverse map is #terminal_id_map.
    */
    //map<string, unsigned long> terminal_map;

    //! symbol_id_map is a map that holds symbol numeric ID mappings to string representations.
    /*!
       Keys in the map are the symbol IDs of type unsigned long and the corresponding strings are the value.
       This is a reverse of #symbol_map.
    */
    map<unsigned long, pair<string, bool>> symbol_id_map;

    /*! The last state used in the WFST. */
    unsigned long int last_state;


    unsigned long FLEEPSILON = 0;

    string FLEEPSILON_STR = "e";


    pair<arc_key, arc_val> last_transition;

    void reverseSymbolMap();

    bool verbose = false;

private:


};

#endif //GRAMMARTEST_FLEWFST_H
