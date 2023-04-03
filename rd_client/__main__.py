import sys
from rd_client.app_modes import get_mode

def main():
    # run selected mode
    sys.exit(get_mode().run())


if __name__ == '__main__':
    main()
