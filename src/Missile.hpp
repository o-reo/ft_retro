/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Missile.hpp                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 12:52:40 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 12:57:38 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MISSILE_HPP
# define MISSILE_HPP

# include "Entity.hpp"
# include <iostream>

class Missile : public Entity
{
	public:
		Missile(unsigned int x, unsigned int y);
		virtual ~Missile(void);

		virtual void	updatePos(void) = 0;
};

#endif