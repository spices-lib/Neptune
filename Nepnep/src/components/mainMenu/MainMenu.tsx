import COLORS from '../../types/colors'
import Menu from './Menu'
import MenuItem from "./MenuItem";
import Separator from "./Separator";

export default function MainMenu() {
    
    return (
        <div className={`fixed top-0 left-0 right-0 h-[22px] flex items-center justify-start w-screen px-2 gap-0 bg-[${COLORS.bgColor}]`}>
            <Menu
                name='File'
            >
                <MenuItem
                    name='New'
                    shortcut='Ctrl + N'
                >
                </MenuItem>
                <MenuItem
                    name='Open'
                    shortcut='Ctrl + O'
                >
                </MenuItem>
                <MenuItem
                    name='Open Recent'
                >
                </MenuItem>
                <MenuItem
                    name='New From Stage Template'
                >
                </MenuItem>
                <MenuItem
                    name='Import'
                >
                </MenuItem>
                <Separator color={COLORS.separatorText_white} height={3}></Separator>
                <MenuItem
                    name='Re-open with New Edit Layer'
                >
                </MenuItem>
                <Separator color={COLORS.separatorText_white} height={3}></Separator>
                <MenuItem
                    name='Save'
                    shortcut='Ctrl + S'
                >
                </MenuItem>
                <MenuItem
                    name='Save With Options'
                    shortcut='Ctrl + Alt + S'
                >
                </MenuItem>
                <MenuItem
                    name='Save As...'
                    shortcut='Shift + Alt + S'
                >
                </MenuItem>
                <MenuItem
                    name='Save Flattened As...'
                >
                </MenuItem>
                <MenuItem
                    name='Export'
                >
                </MenuItem>
                <MenuItem
                    name='Collct As...'
                >
                </MenuItem>
                <Separator color={COLORS.separatorText_white} height={3}></Separator>
                <MenuItem
                    name='Add Reference'
                >
                </MenuItem>
                <MenuItem
                    name='Add Payload'
                >
                </MenuItem>
                <Separator color={COLORS.separatorText_white} height={3}></Separator>
                <MenuItem
                    name='Exit'
                >
                </MenuItem>
            </Menu>
        </div>
    )
}