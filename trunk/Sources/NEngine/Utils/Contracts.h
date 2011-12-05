#ifndef OAW_CONTRACTS_H
#define OAW_CONTRACTS_H

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

website: http://code.google.com/p/openawars/
e-mail: lw.demoscene@gmail.com
**/
#endif

#ifdef CONTRACTS_USE_ABORT
#   include <stdlib.h>
#   define REQUIRE(cond,texte) if(!(cond)) abort()
#   define ENSURE(cond, texte) if(!(cond)) abort()
#   define INVARIANT(cond, texte) if(!(cond)) abort()
#   define BEGIN_INVARIANT_BLOCK(className) void _contract_check_invariants() {
#   define END_INVARIANT_BLOCK }
#   define CHECK_INVARIANTS _contract_check_invariants
#endif

#ifdef CONTRACTS_USE_ASSERT
#   include <assert.h>
#   define REQUIRE(cond, texte) assert(cond)
#   define ENSURE(cond, texte) assert(cond)
#   define INVARIANT(cond, texte) assert(cond)
#   define BEGIN_INVARIANT_BLOCK(className) void _contract_check_invariants() {
#   define END_INVARIANT_BLOCK }
#   define CHECK_INVARIANTS _contract_check_invariants
#endif

#ifdef CONTRACTS_USE_EXCEPTION
#   include <string>
#   include <sstream>
class contract_violation_exception : public std::exception {
    std::string message;
public:
    contract_violation_exception(char const * condition, char const * file, int line)
    {
        std::ostringstream str;
        str << file << " : ligne " << line << " - Violation du contrat : " << condition;
        message = str.str();
    };
    char const * what() const throw() { return message.c_str(); };
    ~contract_violation_exception() throw() {};
};
#   define REQUIRE(cond, texte) if(!(cond)) throw contract_violation_exception(texte, __FILE__, __LINE__)
#   define ENSURE(cond, texte) if(!(cond)) throw contract_violation_exception(texte, __FILE__, __LINE__)
#   define INVARIANT(cond, texte) if(!(cond)) throw contract_violation_exception(texte, __FILE__, __LINE__)
#   define BEGIN_INVARIANT_BLOCK(className) void _contract_check_invariants() {
#   define END_INVARIANT_BLOCK }
#   define CHECK_INVARIANTS _contract_check_invariants
#endif

#ifdef CONTRACTS_NO_CHECK
#   define REQUIRE(cond, texte)
#   define ENSURE(cond, texte)
#   define INVARIANT(cond, texte)
#   define BEGIN_INVARIANT_BLOCK(className)
#   define END_INVARIANT_BLOCK
#   define CHECK_INVARIANTS()
#endif

#ifdef CONTRACTS_NO_PRECONDITION
#   undef REQUIRE
#   define REQUIRE(cond, texte)
#endif

#ifdef CONTRACTS_NO_POSTCONDITION
#   undef ENSURE
#   define ENSURE(cond, texte)
#endif

#ifdef CONTRACTS_NO_INVARIANT
#   undef INVARIANT
#   undef BEGIN_INVARIANT_BLOCK
#   undef END_INVARIANT_BLOCK
#   undef CHECK_INVARIANTS
#   define CHECK_INVARIANTS()
#   define INVARIANT(cond, text)
#   define BEGIN_INVARIANT_BLOCK(className)
#   define END_INVARIANT_BLOCK
#endif

#endif // OAW_CONTRACTS_H
