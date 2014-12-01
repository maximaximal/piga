use <rcube.scad>;
use <buttons.scad>;
use <dimlines.scad>;

joystick_inner_diameter = 5.8;
joystick_outer_width = 6.2;
joystick_allowed_gap = 0.85;
joystick_cover_h = 0.36;
joystick_screw_d = 0.5;
joystick_screw_xy = 0.34;

board_w = 50;
board_h = 16;
board_d = 1.2;

joystick_1_x = (board_w / 8);
joystick_2_x = (board_w / 2) + (board_w / 8);

linewidth = 0.2;
fontscale = 0.13;
fontcolor = [0.1,0.1,0.1];

module screws() {
translate([joystick_outer_width / 2 - joystick_screw_xy, joystick_outer_width / 2 - joystick_screw_xy,0])
		cylinder(d=joystick_screw_d,h=board_d+1,center=true,$fn=10);
translate([-joystick_outer_width / 2 + joystick_screw_xy, joystick_outer_width / 2 - joystick_screw_xy,0])
		cylinder(d=joystick_screw_d,h=board_d+1,center=true,$fn=10);
translate([-joystick_outer_width / 2 + joystick_screw_xy, -joystick_outer_width / 2 + joystick_screw_xy,0])
		cylinder(d=joystick_screw_d,h=board_d+1,center=true,$fn=10);
translate([joystick_outer_width / 2 - joystick_screw_xy, -joystick_outer_width / 2 + joystick_screw_xy,0])
		cylinder(d=joystick_screw_d,h=board_d+1,center=true,$fn=10);
}

module dimensioning() {
	translate([0,-1,0])
		color(fontcolor) dimensions(length=board_w, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([-1,0,0])
		rotate(90)
			color(fontcolor) dimensions(length=board_h, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([joystick_2_x - joystick_inner_diameter / 2,board_h / 2, 0])
			color(fontcolor) dimensions(length=joystick_inner_diameter, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=1,center=true);
	translate([0,board_h / 2 + 8, 0])
		color(fontcolor) dimensions(length=joystick_1_x + joystick_outer_width, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0,center=true);
	translate([joystick_1_x + joystick_outer_width,board_h,0])
		rotate(-90)
		color(fontcolor) line(length=board_h/2, width=linewidth, left_arrow=false, right_arrow=false);
	translate([joystick_1_x + joystick_outer_width,board_h / 2,0])
		rotate(-90)
		color(fontcolor) dimensions(length=board_h / 2, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([joystick_2_x + joystick_outer_width,board_h / 2,0])
		rotate(-90)
		color(fontcolor) dimensions(length=board_h / 2, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0);
	translate([0,board_h / 2 + 9, 0])
		color(fontcolor) dimensions(length=joystick_2_x + joystick_outer_width, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0,center=true);
	translate([joystick_2_x + joystick_outer_width,board_h + 1,0])
		rotate(-90)
		color(fontcolor) line(length=board_h/2 + 1, width=linewidth, left_arrow=false, right_arrow=false);
	translate([0,board_h / 2, 0])
		color(fontcolor) dimensions(length=joystick_1_x, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0,center=true);
	translate([0,-2, 0])
		color(fontcolor) dimensions(length=joystick_2_x, line_width=linewidth, DIM_FONTSCALE=fontscale, loc=0,center=true);
	translate([joystick_2_x,board_h/2,0])
		rotate(-90)
		color(fontcolor) line(length=board_h/2 + 2, width=linewidth, left_arrow=false, right_arrow=false);
}

module controlBoard() {
difference() {
	//The main board cube.
	color([0.7,0.5,0]) cube([board_w,board_h,joystick_allowed_gap]);

	//Joystick 1
	translate([joystick_1_x,board_h / 2, 0]) {
		cylinder(h=board_d + 1, d=joystick_inner_diameter, center=true, $fn=20);
		cube([joystick_outer_width,joystick_outer_width,joystick_cover_h] , center=true);
		translate([0,0,board_d - joystick_cover_h])
			cube([joystick_outer_width,joystick_outer_width,joystick_cover_h] , center=true);

		screws();
	}

	//Joystick 2
	translate([joystick_2_x,board_h / 2, 0]) {
		cylinder(h=board_d + 1, d=joystick_inner_diameter, center=true, $fn=20);
cube([joystick_outer_width,joystick_outer_width,joystick_cover_h] , center=true);
	translate([0,0,board_d - joystick_cover_h])
			cube([joystick_outer_width,joystick_outer_width,joystick_cover_h] , center=true);
		screws();
	}

	translate([joystick_1_x + joystick_outer_width,board_h / 2, -2])
		buttonset();
	translate([joystick_2_x + joystick_outer_width,board_h / 2, -2])
		buttonset();
}

	//translate([joystick_1_x + joystick_outer_width,board_h / 2, -2])
	//	buttonset();
	//translate([joystick_2_x + joystick_outer_width,board_h / 2, -2])
	//	buttonset();

	translate([0,0,board_d + 1]) {
		dimensioning();
	}

	translate([joystick_1_x + joystick_outer_width,board_h / 2, 2])
		controls_button_dimensions();
	translate([joystick_2_x + joystick_outer_width,board_h / 2, 2])
		controls_button_dimensions();
}

controlBoard();
