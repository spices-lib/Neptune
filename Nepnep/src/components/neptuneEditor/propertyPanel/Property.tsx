import SearchBar from '../searchBar/SearchBar'
import PropertyPanel from './PropertyPanel'

export default function Property() {
    const seatchString = ''
    
    return (
        <PropertyPanel
            name='Property'
        >
            <div className='relative fixed w-full h-[30px]'>
                <SearchBar
                    searchString = { seatchString }
                >
                </SearchBar>
            </div>
        </PropertyPanel>
    )
}