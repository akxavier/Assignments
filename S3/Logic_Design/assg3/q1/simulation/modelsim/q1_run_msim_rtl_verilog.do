transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/Aadharsh\ K\ Xavier/Documents/Quartus\ Prime/assg3/q1 {C:/Users/Aadharsh K Xavier/Documents/Quartus Prime/assg3/q1/clk_sr_behavioral.v}

vlog -vlog01compat -work work +incdir+C:/Users/Aadharsh\ K\ Xavier/Documents/Quartus\ Prime/assg3/q1 {C:/Users/Aadharsh K Xavier/Documents/Quartus Prime/assg3/q1/clk_sr_behavioral_tb.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L fiftyfivenm_ver -L rtl_work -L work -voptargs="+acc"  clk_sr_behavioral_tb

add wave *
view structure
view signals
run -all
