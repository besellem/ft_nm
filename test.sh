#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 09:38:46 by besellem          #+#    #+#              #
#    Updated: 2022/05/03 09:42:06 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# clear
make 1>/dev/null
if [ $? -ne 0 ]
then
	exit 1
fi

nm      $* > real
./ft_nm $* > mine

diff -y --color mine real

if [ $? -eq 0 ]
then
	echo "✅ no diff"
else
	echo "❌ diff detected"
fi

rm -f real mine
