/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Boss.hpp                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 14:40:10 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 14:56:11 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BOSS_HPP
# define BOSS_HPP

# include "Entity.hpp"
# include <iostream>

class Boss : public Entity
{
	private:
		unsigned int	_base_y;
		
	public:
		Boss(unsigned int x, unsigned int y);
		virtual ~Boss(void);

		virtual void	updatePos(void);

		static unsigned int liveGlobalBoss;
		virtual bool hasImmunity(const Entity *entity);
};

#endif