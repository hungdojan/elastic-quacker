import pytest

from rd_parser.mappings import *
from rd_parser.key_seqv import *
from rd_parser.key_seqv_parser import KeySeqvParser

@pytest.fixture()
def ksp() -> KeySeqvParser:
    parser = KeySeqvParser(verbose=False)
    return parser


def test_key_seqv():
    modifiers = [Modifier.LALT, Modifier.RCTRL]
    keys = [Key.KEY_A, Key.KEY_B, Key.KEY_0]
    key_seqv = KeySeqv(keys, modifiers=modifiers)

    test_str = str(key_seqv)
    assert '    {0, {KEYBOARD_MODIFIER_LEFTALT|KEYBOARD_MODIFIER_RIGHTCTRL, 0, {HID_KEY_A, HID_KEY_B, HID_KEY_0}}, false},\n' == test_str


def test_empty_list(ksp: KeySeqvParser):
    try:
        ksp.set_last()
    except Exception:
        pytest.fail('Empty list set last failed.')

    assert len(ksp.lof_keyseqvs) == 0


def test_normal_key(ksp: KeySeqvParser):
    test_str = ['a', 'multiple', 'doodle', ',.']
    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    # remove key releases (empty ks.keys)
    key_presses = [ks.keys for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(key_presses) == 6

    # first line
    assert len(key_presses[0]) == 1
    assert set(key_presses[0]) == {normal_mapping[test_str[0]],}

    # second line; [multip, le]
    assert len(key_presses[1]) == 6
    assert set(key_presses[1]) == set([normal_mapping[x] for x in test_str[1][:6]])
    assert len(key_presses[2]) == 2

    # third line; [do, odle]
    assert len(key_presses[3]) == 2
    assert len(key_presses[4]) == 4
    assert set(key_presses[4]) == set([normal_mapping[x] for x in test_str[2][2:]])

    # forth line; [',.']
    assert len(key_presses[5]) == 2
    assert set(key_presses[5]) == set([normal_mapping[x] for x in test_str[3]])


def test_normal_key_shift(ksp: KeySeqvParser):
    test_str = ['A', 'MULTIPLE', 'DOODLE', '{}']
    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    # remove key releases (empty ks.keys)
    key_presses = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(key_presses) == 6

    # first line
    assert len(key_presses[0].keys) == 1
    assert set(key_presses[0].keys) == {normal_mapping[test_str[0].lower()],}
    assert Modifier.LSHIFT in key_presses[0].modifiers

    # second line; [multip, le]
    assert len(key_presses[1].keys) == 6
    assert Modifier.LSHIFT in key_presses[1].modifiers
    assert set(key_presses[1].keys) == set([normal_mapping[x.lower()] for x in test_str[1][:6]])
    assert len(key_presses[2].keys) == 2

    # third line; [do, odle]
    assert len(key_presses[3].keys) == 2
    assert len(key_presses[4].keys) == 4
    assert set(key_presses[4].keys) == set([normal_mapping[x.lower()] for x in test_str[2][2:]])

    # forth line; ['{}']
    assert len(key_presses[5].keys) == 2
    assert set(key_presses[5].keys) == set([normal_mapping[shift_mapping[x]] for x in test_str[3]])


def test_normal_key_combined(ksp: KeySeqvParser):
    pass


def test_delay(ksp: KeySeqvParser):
    pass


def test_special_key(ksp: KeySeqvParser):
    pass


def test_comments(ksp: KeySeqvParser):
    pass


def test_special_sequence(ksp: KeySeqvParser):
    pass


def test_special_sequence_modifiers(ksp: KeySeqvParser):
    pass


def test_special_sequence_hold(ksp: KeySeqvParser):
    pass


def test_errors(ksp: KeySeqvParser):
    pass
