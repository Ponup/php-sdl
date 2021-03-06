<?php
extension_loaded('sdl') or exit('skip SDL extension not loaded');
function skipIncompleteTest() {
	exit('skip test is not complete');
}
function skipIfTravis() {
    if ((bool)getenv('TRAVIS')) {
        exit('skip test if run on Travis');
    }
}
function assertEquals($current, $expected, $assertionMessage) {
	if($current === $expected) {
		printf('PASS: %s.' . PHP_EOL, $assertionMessage);
	} else {
		printf('FAIL: %s. (expected: "%s"; got: "%s")' . PHP_EOL, $assertionMessage, $expected, $current);
	}
}
