$fn = 100;

width = 15.9; //mm
base_height = 4.8; //mm
ring_height = 3.9; //mm
overall_height = 12.9; //mm
wall_thickness = 0.9; //mm

color("red") {
    difference() {
        
        // outer
        union() {
            translate([0, 0, base_height / 2]) cube([width, width, base_height], center=true);
            cylinder(base_height + ring_height, width / 2, width / 2);
            radius = (width / 2) + 1.65;
            difference() {
                translate([0, 0, overall_height - radius]) sphere(radius);
                translate([0, 0, -25 + base_height + ring_height]) cube([50, 50, 50], center=true); // mask
            }
        }
        
        // inner
        union() {
            w = wall_thickness;
            translate([0, 0, base_height / 2 - w - 0.01]) cube([width - 2 * w, width - 2 * w, base_height - 2 * w], center=true);
            cylinder((base_height + ring_height), (width - 2 * w) / 2, (width - 2 * w) / 2);
            
            radius = (width / 2) + 1;
            difference() {
                translate([0, 0, overall_height - radius - w + 0.05]) sphere(radius);
                translate([0, 0, -100 + base_height + ring_height - w + 0.8]) cube([200, 200, 200], center=true); // mask
            }
            
        }
        
        // cutout
        translate([-6, 10, -0.01]) rotate([90, 00, 0]) color("blue") linear_extrude(20) polygon(points=[[0, 0], [12, 0],[12 - 2.5, 2.8], [2.5, 2.8]]);
        
        // Test
        //translate([0, 25, 0]) cube([50, 50, 50], center=true); // mask   
    }
}
