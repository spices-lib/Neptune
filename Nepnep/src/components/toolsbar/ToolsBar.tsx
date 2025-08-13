import SelectionButton from './SelectionButton'
import ShapeSelectionButton from './ShapeSelectionButton'
import { CanvasMode, LayerType } from '../../types/types.d'
import ZoomInButton from './ZoomInButton'
import ZoomOutButton from './ZoomOutButton'

export default function ToolsBar({ 
    canvasState,
    setCanvasState,
    zoomIn,
    zoomOut,
    canZoomIn,
    canZoomOut
}: { 
    canvasState: CanvasState
    setCanvasState: (newState: CanvasState) => void
    zoomIn: () => void
    zoomOut: () => void
    canZoomIn: boolean
    canZoomOut: boolean
}) {
    return (
        <div className='fixed bottom-4 left-1/2 z-10 flex -translate-x-1/2 items-center justify-center rounded-lg bg-white p-1 shadow-[0_0_3px_rgba(0,0,0,0.18)]'>
            <div className='flex justify-center items-center gap-3'>
                <SelectionButton
                    isActive={ 
                        canvasState.mode === CanvasMode.None || 
                        canvasState.mode === CanvasMode.Dragging 
                    }
                    canvasMode={ canvasState.mode }
                    onClick={ (canvasMode) => setCanvasState( canvasMode === CanvasMode.Dragging ? { mode: canvasMode, origin: null } : { mode: canvasMode } )}
                >
                </SelectionButton>
                <ShapeSelectionButton
                    isActive={ 
                        canvasState.mode === CanvasMode.Inserting &&
                        [LayerType.Rectangle, LayerType.Ellipse].includes(canvasState.layerType)
                    }
                    canvasState={ canvasState }
                    onClick={ (layerType) => setCanvasState( { mode: CanvasMode.Inserting, layerType } )}
                >
                </ShapeSelectionButton>
            </div>
            <div className='w-1[px] self-streth bg-black/10'></div>
            <div className='flex items-center justify-center'>
                <ZoomInButton
                    onClick={ zoomIn }
                    disabled={ !canZoomIn }
                >
                </ZoomInButton>
                <ZoomOutButton
                    onClick={ zoomOut }
                    disabled={ !canZoomOut }
                >
                </ZoomOutButton>
            </div>
        </div>
    )
}