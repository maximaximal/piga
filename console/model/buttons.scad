use <dimlines.scad>;

button_diameter = 2.75;
button_h = 3;
button_top_diameter = 3.2;
button_top_cone_d = 2.25;
button_top_h = 0.5;

//Layout multiplier
m = 3/button_diameter;

fontcolor = ([0.1,0.1,0.1]);
linewidth = 0.13;
fontscale = 0.05;

module button() {
	translate([0,0,button_h / 2]) {
		cylinder(d=button_diameter,h=button_h,center=true,$fn=20);
	}
	translate([0,0,button_h])
		cylinder(d1=button_top_diameter,d2=button_top_cone_d + 0.1,h=button_top_h);
	translate([0,0,button_h + button_top_h])
		cylinder(d1=button_top_cone_d,d2=button_top_cone_d - 0.1,h=button_top_h);
}

module controls_button_dimensions() {
	translate([-button_diameter/2, 0, 0])
		color(fontcolor) dimensions(length=button_diameter, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=1);
	translate([0, 5.25 * m, 0])
		color(fontcolor) dimensions(length=0.7 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=1);
	translate([-1,0,0])	
		rotate(90)
			color(fontcolor) dimensions(length=3.85 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([-2,3.85 * m,0])
		color(fontcolor) line(length=12, width=linewidth, left_arrow=false, right_arrow=false);
	translate([0.7 * m,3.85 * m,0])
		rotate(90)
			color(fontcolor) line(length=3, width=linewidth, left_arrow=false, right_arrow=false);
	translate([4 * m, 3.85 * m,0]) {
		rotate(90) {
			color(fontcolor) dimensions(length=5.25 * m-3.85 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=1);color(fontcolor) line(length=3, width=linewidth, left_arrow=false, right_arrow=false);}}
	translate([7.55 * m, 3.85 * m,0]) {
		rotate(90) {
			color(fontcolor) dimensions(length=4.65 * m-3.85 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=1);color(fontcolor) line(length=3, width=linewidth, left_arrow=false, right_arrow=false);}}
	
	translate([0.7 * m,5.25 * m,0])
		color(fontcolor) dimensions(length=4 * m-0.7 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([4 * m, 5.25 * m,0])
		color(fontcolor) dimensions(length=7.55 * m - 4 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([-1,0,0])
		color(fontcolor) line(length=11, width=linewidth, left_arrow=false, right_arrow=false);
	translate([3.3 * m,0,0]) {
		rotate(90) {
			color(fontcolor) dimensions(length=1.4 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=1);color(fontcolor) line(length=3, width=linewidth, left_arrow=false, right_arrow=false);}}
	translate([6.9 * m,0,0]) {
		rotate(90) {
			color(fontcolor) dimensions(length=0.8 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=1);color(fontcolor) line(length=3, width=linewidth, left_arrow=false, right_arrow=false);}}
	rotate(90)
		color(fontcolor) line(length=7.2, width=linewidth, left_arrow=false, right_arrow=false);
	translate([0, 1,0])
		color(fontcolor) dimensions(length=3.3 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([3.6, 1,0])
		color(fontcolor) dimensions(length=6.9 * m-3.3 * m, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
}

module buttonset() {
	//Generate this layout: http://www.slagcoin.com/joystick/layout/sega1_l.png
	button();

	translate([0.7 * m,3.85 * m,0])
		button();
	translate([3.3 * m,1.4 * m,0])
		button();
	translate([6.9 * m,0.8 * m,0])
		button();
	translate([4 * m, 5.25 * m,0])
		button();
	translate([7.55 * m, 4.65 * m,0])
		button();
	//translate([10.3 * m,-0.7 * m,0])
	//	button();
	//translate([10.95 * m, 3.15 * m,0])
	//	button();

	translate([0,0,5])
		controls_button_dimensions();
}

buttonset();