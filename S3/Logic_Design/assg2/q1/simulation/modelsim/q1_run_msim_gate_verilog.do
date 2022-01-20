transcript on
if {[file exists gate_work]} {
	vdel -lib gate_work -all
}
vlib gate_work
vmap work gate_work

vlog -vlog01compat -work work +incdir+. {q1.vo}

vlog -vlog01compat -work work +incdir+C:/Users/Aadharsh\ K\ Xavier/Documents/Quartus\ Prime/assg2/q1 {C:/Users/Aadharsh K Xavier/Documents/Quartus Prime/assg2/q1/fa_dataflow_tb.v}

vsim -t 1ps -L altera_ver -L altera_lnsim_ver -L fiftyfivenm_ver -L gate_work -L work -voptargs="+acc"  fa_dataflow_tb

add wave *
view structure
view signals
run -all
