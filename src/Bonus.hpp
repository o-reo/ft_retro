/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Bonus.hpp                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:54:30 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 13:12:29 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BONUS_HPP
# define BONUS_HPP

# include "Entity.hpp"
#include <ctime>
# include <iostream>

class Bonus : public Entity
{
	public:
		Bonus(unsigned int x, unsigned int y);
		virtual ~Bonus(void);

		virtual void	updatePos(void);
};

#endif