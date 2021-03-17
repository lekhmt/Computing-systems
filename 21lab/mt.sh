#! /usr/bin/env bash

# на вход поступают два файла - файл с программой {PROGRAM} и файл с входными даннфми {INPUT}
# файл с программой должен содержать строки вида "q0, a0, a1, q1"


usage (){
	STR="Использование: ${0} {PROGRAM} {INPUT}"
	if [[ $1 == 'e' ]]; then
		echo "$STR" >&2
		exit 1
	else
		echo "$STR"
	fi
}

if [[ $# != 2 ]]; then
	usage 'e'
fi

PROG="$1"
INPUT="$2"

Q='0'										# начальное состояние "q0"
LEFT="$(cat "$2" | head -n1)" 							# часть строки левее головки
RIGHT='' 									# часть строки правее головки
CUR=' ' 									# знак из рабочей ячейки "a0"

STOP='q'									# остановка работы скрипта
NEXT='n'									# выполнение одного шага
HELP='?'									# вызов справки
RUN='r'										# выполнение всей программы

# выполнение одного шага; "$1" - строка с командой
step (){						

	A="$(echo "$1" | cut -f3 -d',')"					# знак действия "a1"
	Q="$(echo "$1" | cut -f4 -d',')"					# состояние, в которое должна будет перейти головка "q1"
	
	if [[ "$A" != '=' ]]; then
	
		case "$A" in
		
			"<") 
				if [[ "$LEFT" == '' ]]; then
					echo "Выход за край ленты."
					exit 2
				fi
				TMP="$CUR"
				CUR="${LEFT:${#LEFT}-1:1}"
				LEFT="${LEFT:0:${#LEFT}-1}"
				RIGHT="$TMP$RIGHT"
			;;
			
			">") 
				if [[ "$RIGHT" == '' ]]; then
					RIGHT=' '
				fi
				TMP="$CUR"
				CUR="${RIGHT:0:1}"
				LEFT="$LEFT$TMP"
				RIGHT="${RIGHT:1:${#RIGHT}}"
			;;
			
			*) 
				CUR="$A" 
			;;
			
		esac
	
	fi
	
	if [[ "$CUR" == '' ]]; then
		echo "Нужный переход не найден. Ошибка в программе."	
		exit 3
	fi	
		
	NEWRES="${1} '${LEFT}[${CUR}]$RIGHT'"
	echo "$NEWRES"
	if [[ "$RES" == "$NEWRES" ]]; then
		if COMMAND="$(grep "^${Q},${CUR}" "$PROG")"; then
			echo "Программа завершилась успехом. Результат:"
			echo "'$(cat "$INPUT") ' -> '$LEFT$CUR${RIGHT}'"
		fi
		exit 4
	fi
	RES="$NEWRES"

}

#выполнение всей программы
run (){ 
	while COMMAND="$(grep "^${Q},${CUR}" "$PROG")"
	if [[ "$COMMAND" == '' ]]; then
		echo "Нужный переход не найден. Ошибка в программе."
		exit 5
	fi
	do
		step "$COMMAND" 
	done
}

main (){
	echo "Для получения справки введите \"?\"."
	read M

	while [[ "$M" != 'q' ]]
	do

		case "$M" in
		
			"$HELP")
				usage
				echo "Для работы с программой используются следующие команды:"
				echo "--- \"n\" - выполнение одного шага"
				echo "--- \"r\" - выполнение всей программы"
				echo "--- \"?\" - вызов справки"
				echo "--- \"q\" - завершение работы программы"	
			;;
			
			"$NEXT")
				COMMAND="$(grep "^${Q},${CUR}" "$PROG")"   
				step "$COMMAND"
			;;
	
			"$RUN")
				run
			;;
	
			*)
				echo "Совпадений не найдено. Попробуйте ещё раз."
			;;
	
		esac
	
		read M	

	done
}

main

